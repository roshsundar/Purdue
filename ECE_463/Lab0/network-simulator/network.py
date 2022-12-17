# The code is subject to Purdue University copyright policies.
# DO NOT SHARE, DISTRIBUTE, OR POST ONLINE
#

import sys
import threading
import json
import pickle
import signal
import time
import os.path
import queue
from collections import defaultdict
from client import Client
from link import Link
from router import Router


class Network:
    """Network class maintains all clients, routers, links, and confguration"""

    def __init__(self, netJsonFilepath, routerClass):
        """Create a new network from the parameters in the file at
           netJsonFilepath."""

        # parse configuration details
        netJsonFile = open(netJsonFilepath, 'r')
        netJson = json.load(netJsonFile)
        self.latencyMultiplier = 100
        self.heartbeatTime = netJson["heartbeatTime"] * self.latencyMultiplier
        self.endTime = netJson["endTime"] * self.latencyMultiplier
        self.clientSendRate = netJson["clientSendRate"]*self.latencyMultiplier

        # parse and create routers, clients, and links
        self.routers = self.parserouters(netJson["routers"], routerClass)
        self.clients = self.parseClients(netJson["clients"], self.clientSendRate)
        self.links = self.parseLinks(netJson["links"])

        # parse link changes
        if "changes" in netJson:
            self.changes = self.parseChanges(netJson["changes"])
        else:
            self.changes = None

        self.threads = []


    def parserouters(self, routerParams, routerClass):
        """Parse routers from routerParams dict"""
        routers = {}
        for addr in routerParams:
            routers[addr] = routerClass(addr, self.heartbeatTime)
        return routers


    def parseClients(self, clientParams, clientSendRate):
        """Parse clients from clientParams dict"""
        clients = {}
        for addr in clientParams:
            clients[addr] = Client(addr, clientParams, clientSendRate)
        return clients


    def parseLinks(self, linkParams):
        """Parse links from linkParams dict"""
        links = {}
        for addr1, addr2, p1, p2, c in linkParams:
            link = Link(addr1, addr2, c, self.latencyMultiplier)
            links[(addr1,addr2)] = (p1, p2, c, link)
        return links


    def parseChanges(self, changesParams):
        """Parse link changes from changesParams dict"""
        changes = queue.PriorityQueue()
        for change in changesParams:
            changes.put(change)
        return changes


    def clearQueues(self):
        for addr1,addr2 in self.links:
            _, _, _, link = self.links[(addr1,addr2)]
            while not link.q12.empty():
                link.q12.get_nowait()
            while not link.q21.empty():
                link.q21.get_nowait()


    def run(self):
        """Run the network.  Start threads for each client and router. Start
           thread to track link changes.  Wait until
           end time and then print final output"""
        for router in self.routers.values():
            thread = router_thread(router)
            thread.start()
            self.threads.append(thread)
        for client in self.clients.values():
            thread = client_thread(client)
            thread.start()
            self.threads.append(thread)
        self.addLinks()
        if self.changes:
            self.handleChangesThread = handle_changes_thread(self)
            self.handleChangesThread.start()
        signal.signal(signal.SIGINT, self.handleInterrupt)
        time.sleep(self.endTime/float(1000))
        self.clearQueues()
        for client in self.clients.values():
            client.sendDataPackets()
        time.sleep(10)
        self.joinAll()


    def addLinks(self):
        """Add links to clients and routers"""
        for addr1, addr2 in self.links:
            p1, p2, c, link = self.links[(addr1, addr2)]
            if addr1 in self.clients:
                self.clients[addr1].changeLink(("add", link))
            if addr2 in self.clients:
                self.clients[addr2].changeLink(("add", link))
            if addr1 in self.routers:
                self.routers[addr1].changeLink(("add", p1, addr2, link, c))
            if addr2 in self.routers:
                self.routers[addr2].changeLink(("add", p2, addr1, link, c))


    def handleChanges(self):
        """Handle changes to links. Run this method in a separate thread.
           Uses a priority queue to track time of next change"""
        startTime = time.time()*1000
        while not self.changes.empty():
            changeTime, target, change = self.changes.get()
            currentTime = time.time()*1000
            waitTime = (changeTime*self.latencyMultiplier + startTime) - currentTime
            if waitTime > 0:
                time.sleep(waitTime/float(1000))
            # link changes
            if change == "up":
                addr1, addr2, p1, p2, c = target
                link = Link(addr1, addr2, c, self.latencyMultiplier)
                self.links[(addr1,addr2)] = (p1, p2, c, link)
                self.routers[addr1].changeLink(("add", p1, addr2, link, c))
                self.routers[addr2].changeLink(("add", p2, addr1, link, c))
            elif change == "down":
                addr1, addr2, = target
                p1, p2, _, link = self.links[(addr1, addr2)]
                self.routers[addr1].changeLink(("remove", p1))
                self.routers[addr2].changeLink(("remove", p2))


    def joinAll(self):
        if self.changes:
            self.handleChangesThread.join()
        for thread in self.threads:
            thread.join()


    def handleInterrupt(self, signum, _):
        self.joinAll()
        quit()



def main():
    """Main function parses command line arguments and runs network"""
    if len(sys.argv) < 2:
        sys.stdout.write("Usage: python network.py [networkSimulationFile.json]\n")
        return
    netCfgFilepath = sys.argv[1]
    routerClass = Router
    net = Network(netCfgFilepath, routerClass)
    net.run()
    return

# Extensions of threading.Thread class

class router_thread(threading.Thread):

    def __init__(self, router):
        threading.Thread.__init__(self)
        self.router = router

    def run(self):
        self.router.runRouter()

    def join(self, timeout=None):
        self.router.keepRunning = False
        super(router_thread, self).join(timeout)

class client_thread(threading.Thread):

    def __init__(self, client):
        threading.Thread.__init__(self)
        self.client = client

    def run(self):
        self.client.runClient()

    def join(self, timeout=None):
        self.client.keepRunning = False
        super(client_thread, self).join(timeout)

class handle_changes_thread(threading.Thread):

    def __init__(self, network):
        threading.Thread.__init__(self)
        self.network = network

    def run(self):
        self.network.handleChanges()


if __name__ == "__main__":
    main()
