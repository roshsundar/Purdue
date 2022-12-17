# The code is subject to Purdue University copyright policies.
# DO NOT SHARE, DISTRIBUTE, OR POST ONLINE
#

from copy import deepcopy

class Packet:
    """Packet class defines packets that clients and routers
       send in the simulated network"""

    # Access these constants from other files
    # as Packet.DATA or Packet.CONTROL
    DATA = 1
    CONTROL = 2

    def __init__(self, kind, srcAddr, dstAddr, content=None):
        """create a new packet"""
        self.kind = kind        # either DATA or CONTROL
        self.srcAddr = srcAddr  # address of the source of the packet
        self.dstAddr = dstAddr  # address of the destination of the packet
        self.content = content  # content of the packet (must be a string)


    def copy(self):
        """Create a deepcopy of the packet.  This gets called automatically
           when the packet is sent to avoid aliasing issues"""
        p = Packet(self.kind, self.srcAddr, self.dstAddr, content=deepcopy(self.content))
        return p


    def isData(self):
        """Returns True if the packet is a DATA packet"""
        return self.kind == Packet.DATA


    def isControl(self):
        """Returns True if the packet is a CONTROL packet"""
        return self.kind == Packet.CONTROL