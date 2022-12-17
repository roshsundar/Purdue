# The code is subject to Purdue University copyright policies.
# DO NOT SHARE, DISTRIBUTE, OR POST ONLINE
#

import sys
import time
from switch import Switch
from link import Link
from client import Client
from packet import Packet


class STPswitch(Switch):
    """STP, MAC learning and MAC forwarding implementation"""

    def __init__(self, addr, heartbeatTime):
        Switch.__init__(self, addr, heartbeatTime)  # initialize superclass - don't remove
        """add your own class fields and initialization code here"""
        self.STPview = [addr, '0', addr, addr] # R = current root, Cost(X,R) = cost from X to R, X = current switch, H = next hop ---- initialized to [X, 0, X, X]
        self.ForwardTable = {} # stores data in form of <Source Address, Port>

    def handlePacket(self, port, packet):
        """process incoming packet"""

        if packet.isControl():
            # turn packet content back into an STPview format
            STPcontent = list(packet.content.split(" "))

            # get the link the STP packet took to get here
            l = self.links[port]

            # link active/inactive check
            if self.STPview[3] != STPcontent[2] and STPcontent[3] != self.addr:
                # inactive
                l.status = Link.INACTIVE # set link to be inactive
                # remove all entries from forwarding table that cant be reached now
                self.ForwardTable = {s:p for s,p in self.ForwardTable.items() if p != port}
            else:
                # active
                l.status = Link.ACTIVE # set link to be active

            newView = self.STPview.copy()
            c = str(l.cost + int(STPcontent[1]))
            # Case 0: ignore advertisements from neighbors whose next hop is you
            if STPcontent[3] == self.addr:
                # Do not update current STPview
                pass
            # Case 1: advertisement from current hop
            elif self.STPview[3] == STPcontent[2]:
                if STPcontent[0] < self.STPview[2]:
                    newView = [STPcontent[0], c, self.addr, STPcontent[2]]
                else:
                    newView = [self.addr, '0', self.addr, self.addr]
            # Case 2: advertisement not from current hop
            elif self.STPview[3] != STPcontent[2]:
                if STPcontent[0] < self.STPview[0]:
                    newView = [STPcontent[0], c, self.addr, STPcontent[2]]
                    l.status = Link.ACTIVE
                elif STPcontent[0] == self.STPview[0] and self.STPview[1] < c:
                    newView = [STPcontent[0], c, self.addr, STPcontent[2]]
                    l.status = Link.ACTIVE
                elif STPcontent[0] == self.STPview[0] and self.STPview[1] == c and STPcontent[2] < self.STPview[3]:
                    newView = [STPcontent[0], c, self.addr, STPcontent[2]]
                    l.status = Link.ACTIVE
            
            # check if new view is different from current view.
            if newView != self.STPview:
                # new view is different, so update view
                self.STPview = newView
                # send current STP view to all phsically linked neighbors
                for port in self.links.keys():
                    STPcontent = ' '.join([str(elem) for elem in self.STPview]) # convert STPview list into string
                    STPpacket = Packet(Packet.CONTROL, self.addr, 'X', STPcontent)
                    self.send(port, STPpacket)

        if packet.isData():
            if self.links[port].status == Link.ACTIVE: # only consider packets from active links
                # MAC learning
                self.ForwardTable[packet.srcAddr] = port

                # MAC forwarding
                if packet.dstAddr == 'X': # boadcast packet
                    # send broadcast on all active ports except the one the packet was recieved on
                    for p in self.links.keys():
                        if p != port and self.links[p].status == Link.ACTIVE:
                            self.send(p, packet)
                elif packet.dstAddr in self.ForwardTable.keys(): # if destination address in forwarding table
                    if self.ForwardTable[packet.dstAddr] == port or self.links[self.ForwardTable[packet.dstAddr]].status == Link.INACTIVE:
                        # drop packet, dont want to sent back on same port packet arrived
                        pass
                    else:
                        # send packet out
                        self.send(self.ForwardTable[packet.dstAddr], packet)
                else:
                    # broadcast the packet on all active ports except the one the packet was recieved on
                    for p in self.links.keys():
                        if p != port and self.links[p].status == Link.ACTIVE:
                            self.send(p, packet)

    def handleNewLink(self, port, endpoint, cost):
        """a new link has been added to switch port and initialized, or an existing
        link cost has been updated. Implement any routing/forwarding action that
        you might want to take under such a scenario"""
        self.STPview = [self.addr, '0', self.addr, self.addr]
        # send current STP view to all phsically linked neighbors
        for port in self.links.keys():
            STPcontent = ' '.join([str(elem) for elem in self.STPview]) # convert STPview list into string
            STPpacket = Packet(Packet.CONTROL, self.addr, 'X', STPcontent)
            self.send(port, STPpacket)


    def handleRemoveLink(self, port, endpoint):
        """an existing link has been removed from the switch port. Implement any 
        routing/forwarding action that you might want to take under such a scenario"""
        self.STPview = [self.addr, '0', self.addr, self.addr]
        # send current STP view to all phsically linked neighbors
        for port in self.links.keys():
            STPcontent = ' '.join([str(elem) for elem in self.STPview]) # convert STPview list into string
            STPpacket = Packet(Packet.CONTROL, self.addr, 'X', STPcontent)
            self.send(port, STPpacket)


    def handlePeriodicOps(self):
        """handle periodic operations. This method is called every heartbeatTime.
        You can change the value of heartbeatTime in the json file"""

        # send current STP view to all phsically linked neighbors
        for port in self.links.keys():
            STPcontent = ' '.join([str(elem) for elem in self.STPview]) # convert STPview list into string
            STPpacket = Packet(Packet.CONTROL, self.addr, 'X', STPcontent)
            self.send(port, STPpacket)