# The code is subject to Purdue University copyright policies.
# DO NOT SHARE, DISTRIBUTE, OR POST ONLINE
#

import sys
from collections import defaultdict
from router import Router
from packet import Packet
from json import dumps, loads


class PQEntry:

    def __init__(self, addr, cost, next_hop):
        self.addr = addr
        self.cost = cost
        self.next_hop = next_hop

    def __lt__(self, other):
         return (self.cost < other.cost)

    def __eq__(self, other):
         return (self.cost == other.cost)


class LSrouter(Router):
    """Link state routing and forwarding implementation"""

    def __init__(self, addr, heartbeatTime):
        Router.__init__(self, addr, heartbeatTime)  # initialize superclass - don't remove
        self.graph = {} # A dictionary with KEY = router
                        # VALUE = a list of lists of all its neighbor routers/clients and the cost to each neighbor
                        # {router: [[neighbor_router_or_client, cost]...], ...}
        self.graph[self.addr] = []
        """add your own class fields and initialization code here"""
        self.rtable = {} # dictionary of dictionaries {'dest': {'dest': ___, 'cost': ___, 'hop': ___, 'port': ___}, ...}
        self.seqtable = {}  # dictionary of numbers {'router': seqnum, ...}  -  stores highest seqnum recieved from every router
        self.LSA = {} # {'router': [[neighbor_router_or_client, cost]...], seqnum: ___}
        self.seqnum = 1


    def handlePacket(self, port, packet):
        """process incoming packet"""
        """parameters:
        port : the router port on which the packet was received
        packet : the received packet"""
        
        # data packet
        if packet.isData():
            if packet.dstAddr in self.rtable:
                self.send(self.rtable[packet.dstAddr]["port"], packet)
        
        # control packet
        if packet.isControl():
            content = loads(packet.content)

            # seqnum check
            if packet.srcAddr not in self.seqtable or content["seqnum"] > self.seqtable[packet.srcAddr]:
                # update highest seqnum for source router
                self.seqtable[packet.srcAddr] = content["seqnum"]

                # update graph
                self.graph[packet.srcAddr] = content["router"]

                # broadcast recieved LSA to all neighbors except sender
                for p in self.links.keys():
                    if p != port:
                        self.send(p, packet)

                # run dijkstra
                finishedQ = self.dijkstra()

                # update routing table
                for pqentry in finishedQ:
                    # create entry vector for routing table
                    entry = {
                        'dest' : pqentry.addr,
                        'cost' : pqentry.cost,
                        'hop'  : pqentry.next_hop
                    }

                    # fetch the port
                    for p in self.links.keys():
                        if self.links[p].get_e2(self.addr) == pqentry.next_hop:
                            entry['port'] = p
                    
                    # update/add entry in routing table
                    self.rtable[pqentry.addr] = entry


    def handleNewLink(self, port, endpoint, cost):
        """a new link has been added to router port and initialized, or an existing
        link cost has been updated. This information has already been updated in the
        "links" data structure in router.py. Implement any routing/forwarding action
        that you might want to take under such a scenario"""
        """parameters:
        port : router port of the new link / the existing link whose cost has been updated
        endpoint : the node at the other end of the new link / the exisitng link whose cost has been updated
        (this end of the link is self.addr)
        cost : cost of the new link / new cost of the exisitng link whose cost has been updated"""

        # update graph
        for neighbor in self.graph[self.addr]:
            if neighbor[0] == endpoint:
                self.graph[self.addr].remove(neighbor)
        self.graph[self.addr].append([endpoint,cost])

        # update LSA
        self.LSA = {
            'router' : self.graph[self.addr],
            'seqnum' : self.seqnum
        }

        # broadcast LSA to all neighbors
        for p in self.links.keys():
            content = dumps(self.LSA)
            packet = Packet(Packet.CONTROL, self.addr, 'X', content)
            self.send(p, packet)
        self.seqnum += 1

        # run dijkstra
        finishedQ = self.dijkstra()

        # update routing table
        for pqentry in finishedQ:
            # create entry vector for routing table
            entry = {
                'dest' : pqentry.addr,
                'cost' : pqentry.cost,
                'hop'  : pqentry.next_hop
            }

            # fetch the port
            for p in self.links.keys():
                if self.links[p].get_e2(self.addr) == pqentry.next_hop:
                    entry['port'] = p
            
            # update/add entry in routing table
            self.rtable[pqentry.addr] = entry
        

    def handleRemoveLink(self, port, endpoint):
        """an existing link has been removed from the router port. This information
        has already been updated in the "links" data structure in router.py. Implement any 
        routing/forwarding action that you might want to take under such a scenario"""
        """parameters:
        port : router port from which the link has been removed
        endpoint : the node at the other end of the removed link
        (this end of the link is self.addr)"""
        # update graph
        for neighbor in self.graph[self.addr]:
            if neighbor[0] == endpoint:
                self.graph[self.addr].remove(neighbor)
        
        # update LSA
        self.LSA = {
            'router' : self.graph[self.addr],
            'seqnum' : self.seqnum
        }

        # broadcast LSA to all neighbors
        for p in self.links.keys():
            content = dumps(self.LSA)
            packet = Packet(Packet.CONTROL, self.addr, 'X', content)
            self.send(p, packet)
        self.seqnum += 1

        # run dijkstra
        finishedQ = self.dijkstra()

        # update routing table
        for pqentry in finishedQ:
            # create entry vector for routing table
            entry = {
                'dest' : pqentry.addr,
                'cost' : pqentry.cost,
                'hop'  : pqentry.next_hop
            }

            # fetch the port
            for p in self.links.keys():
                if self.links[p].get_e2(self.addr) == pqentry.next_hop:
                    entry['port'] = p
            
            # update/add entry in routing table
            self.rtable[pqentry.addr] = entry
        

    def handlePeriodicOps(self):
        """handle periodic operations. This method is called every heartbeatTime.
        You can change the value of heartbeatTime in the json file"""
        
        # broadcast LSA to all neighbors
        for p in self.links.keys():
            content = dumps(self.LSA)
            packet = Packet(Packet.CONTROL, self.addr, 'X', content)
            self.send(p, packet)
        self.seqnum += 1


    def dijkstra(self):
        """An implementation of Dijkstra's shortest path algorithm.
        Operates on self.graph datastructure and returns the cost and next hop to
        each destination node in the graph as a List (finishedQ) of type PQEntry"""
        priorityQ = []
        finishedQ = [PQEntry(self.addr, 0, self.addr)]
        for neighbor in self.graph[self.addr]:
            priorityQ.append(PQEntry(neighbor[0], neighbor[1], neighbor[0]))
        priorityQ.sort(key=lambda x: x.cost)

        while len(priorityQ) > 0:
            dst = priorityQ.pop(0)
            finishedQ.append(dst)
            if not(dst.addr in self.graph.keys()):
                continue
            for neighbor in self.graph[dst.addr]:
                #neighbor already exists in finishedQ
                found = False
                for e in finishedQ:
                    if e.addr == neighbor[0]:
                        found = True
                        break
                if found:
                    continue
                newCost = dst.cost + neighbor[1]
                #neighbor already exists in priorityQ
                found = False
                for e in priorityQ:
                    if e.addr == neighbor[0]:
                        found = True
                        if newCost < e.cost:
                            e.cost = newCost
                            e.next_hop = dst.next_hop
                        break
                if not found:
                    priorityQ.append(PQEntry(neighbor[0], newCost, dst.next_hop))

                priorityQ.sort(key=lambda x: x.cost)

        return finishedQ

