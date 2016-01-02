# Simple Router Simulator
School homework that emulates the working of a router.  
It emulates a communication between a router and a host using an ICMP packet sent from one host to another one through the net.

## How it works
Initially the router loads the routing table from the file. The routing table contains the list of the hosts connected to net and the jumps that the ICMP packet has to do to reach the destination.  
Then it sends a signal to all the other devices to check if there are changes. In the case that there are changes in the graph of the net, it updates the table. saves it in the file and reload it.  
When the router has loaded the table, it goes in listen-mode where it waits for a connection from a host or an another router.  
When a connection is established, the router breaks up the ICMP packet and gets the destination IP. Using Dijkstra's algorithm it gets the shortest path to reach the destination and then it sends the packet in the net towards the destination.  

## Test environment
**Processor**: AMD Phenom(tm) II P960 Quad-Core Processor 1.8GHz
**GCC version**: gcc version 4.9.2 (Debian 4.9.2-10)

## Results  
Results of the computation time of the Dijkstra's algorithm. (time in seconds)

### Version 1.0 (easiest algorithm to generate prime numbers)  
#### Sending a packet from one host to another through 10 intermediates routers.
...

## Contributors
Roberto Belingheri (Dijkstra's algorithm) and host-device code.

## Info/Contacts:
**Author**: Luca Bertoni  
**Version**: 0.1  
**Contacts**:  

	Email: luca.bertoni24@gmail.com

	Facebook: https://www.facebook.com/LucaBertoniLucaBertoni
