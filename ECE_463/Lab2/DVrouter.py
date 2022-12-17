# The code is subject to Purdue University copyright policies.
# DO NOT SHARE, DISTRIBUTE, OR POST ONLINE
#

import sys
from collections import defaultdict
from router import Router
from packet import Packet
from json import dumps, loads

class DVrouter(Router):
    """Distance vector routing and forwarding implementation"""

    def __init__(self, addr, heartbeatTime, infinity):
        Router.__init__(self, addr, heartbeatTime)  # initialize superclass - don't remove
        self.infinity = infinity
        """add your own class fields and initialization code here"""
        self.rtable = {} # dictionary of dictionaries {'dest': {'dest': ___, 'cost': ___, 'hop': ___, 'port': ___}, ...}

    def handlePacket(self, port, packet):
        """process incoming packet"""
        """parameters:
        port : the router port on which the packet was received
        packet : the received packet"""
        
        # data packet
        if packet.isData():
            # send only if dest in routing table, and link is available
            if (packet.dstAddr in self.rtable) and (self.rtable[packet.dstAddr]["cost"] < self.infinity) and (self.rtable[packet.dstAddr]["hop"] != None):
                self.send(self.rtable[packet.dstAddr]["port"], packet)
        
        # control packet
        if packet.isControl():
            content = loads(packet.content)
            change_flag = False

            for addr in content.keys():
                # split horizon check
                if content[addr]["hop"] == self.addr:
                    pass
                else:
                    # create the distance vector
                    dv = {
                        'dest' : addr,
                        'cost' : content[addr]["cost"] + self.links[port].cost,
                        'hop'  : packet.srcAddr,
                        'port' : port
                    }

                    # router does not know of addr
                    if addr not in self.rtable:
                        # add the dv to routing table
                        self.rtable[addr] = dv
                        change_flag = True
                    # case 1: router knows of addr, advertisement from current next hop to addr
                    elif dv["hop"] == self.rtable[addr]["hop"]:
                        # max infinity check
                        if dv["cost"] >= self.infinity:
                            self.rtable[addr] = {
                                'dest' : addr,
                                'cost' : self.infinity,
                                'hop'  : None,
                                'port' : None
                            }
                        # update routing table entry for addr
                        else:
                            self.rtable[addr] = dv
                        change_flag = True
                    # case 2: router knows of addr, advertisement from non-current next hop to addr, and lower cost path to addr is available
                    elif dv["cost"] < self.rtable[addr]["cost"]:
                        # update routing table entry for addr
                        self.rtable[addr] = dv
                        change_flag = True
            
            # if routing table view has changed
            if change_flag == True:
                # advertise routing table to all neighbors
                for p in self.links.keys():
                    content = dumps(self.rtable)
                    packet = Packet(Packet.CONTROL, self.addr, 'X', content)
                    self.send(p, packet)

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

        # routing table - update entry if it exists, add entry otherwise
        self.rtable[endpoint] = {
                    'dest' : endpoint,
                    'cost' : cost,
                    'hop'  : endpoint,
                    'port' : port
        }

        # advertise routing table to all neighbors
        for p in self.links.keys():
            content = dumps(self.rtable)
            packet = Packet(Packet.CONTROL, self.addr, 'X', content)
            self.send(p, packet)

    def handleRemoveLink(self, port, endpoint):
        """an existing link has been removed from the router port. This information
        has already been updated in the "links" data structure in router.py. Implement any 
        routing/forwarding action that you might want to take under such a scenario"""
        """parameters:
        port : router port from which the link has been removed
        endpoint : the node at the other end of the removed link
        (this end of the link is self.addr)"""

        # search for the entry that is no longer reachable in routing table
        # update entry in routing table to reflect un-reachability
        for entry in self.rtable:
            if endpoint == self.rtable[entry]["hop"]:
                self.rtable[entry] = {
                    'dest' : entry,
                    'cost' : self.infinity,
                    'hop'  : None,
                    'port' : None
                }
        
        # advertise routing table to all neighbors
        for p in self.links.keys():
            content = dumps(self.rtable)
            packet = Packet(Packet.CONTROL, self.addr, 'X', content)
            self.send(p, packet)

    def handlePeriodicOps(self):
        """handle periodic operations. This method is called every heartbeatTime.
        You can change the value of heartbeatTime in the json file"""

        # advertise routing table to all neighbors
        for p in self.links.keys():
            content = dumps(self.rtable)
            packet = Packet(Packet.CONTROL, self.addr, 'X', content)
            self.send(p, packet)