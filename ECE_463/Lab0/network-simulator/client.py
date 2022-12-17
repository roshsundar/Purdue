# The code is subject to Purdue University copyright policies.
# DO NOT SHARE, DISTRIBUTE, OR POST ONLINE
#

import time
import sys
import queue
from packet import Packet


class Client:
    """Client class sends DATA packets into the network."""

    def __init__(self, addr, allClients, sendRate):
        """Inititaliza parameters"""
        self.addr = addr
        self.allClients = allClients
        self.sendRate = sendRate
        self.link = None
        self.linkChanges = queue.Queue()
        self.keepRunning = True


    def changeLink(self, change):
        """Add a link to the client.
           The change argument should be a tuple ('add', link)"""
        self.linkChanges.put(change)


    def sendDataPackets(self):
        """Send a single DATA packet into the network"""
        packet = Packet(Packet.DATA, self.addr, 'X', "Packet from client "+str(self.addr))
        if self.link:
            self.link.send(packet, self.addr)


    def runClient(self):
        """Main loop of client"""
        while self.keepRunning:
            time.sleep(0.1)
            try:
                change = self.linkChanges.get_nowait()
                if change[0] == "add":
                    self.link = change[1]
            except queue.Empty:
                pass
            if self.link:
                packet = self.link.recv(self.addr)
