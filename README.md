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

## Example of network
The network used actually in test is the following.
```
Destination  | Next Hop  |Weight
--------------------------------
192.168.0.11 |192.168.0.4|   0
192.168.0.4  |192.168.0.3|   2
192.168.0.4  |192.168.0.5|   1
192.168.0.4  |192.168.0.6|   6
192.168.0.3  |192.168.0.2|   3
192.168.0.5  |192.168.0.2|   5
192.168.0.5  |192.168.0.6|   2
192.168.0.2  |X          |   1
192.168.0.6  |X          |   3

X = Direct connection, there aren't any router between the destination and the current position.

```

This means that there are two hosts: source(H0, ip: 192.168.0.10) and destination(H1, ip: 192.168.0.11). There are six routers (A,B,C,D,E,F) connected each other in this way: A -> B & F, B -> F & E, C -> D, D -> E & F, E -> B & D & F, F -> A & B & D & E.


```
                         B       3       C
                         O---------------O
                        /|\               \
                       / | \               \
                    1 /  |  \               \ 
                     /   |   \               \ 2
                    /    |    \               \
                   /     |     \               \
H0               A/      |      \               \D                H1
O----------------O       |1      \               O----------------O
                  \      |        \       6    //
                   \     |         \        /  /
                    \    |          \   /     /
                     \   |          /\       /
                    3 \  |       /    \     / 1
                       \ |    /        \   /
                        \| /            \ /
                         O---------------O
                       	 F       2       E
```
The numbers in the graph are the weights of links between routers.

Ip of the routers are:  
A = 192.168.0.1  
B = 192.168.0.2  
C = 192.168.0.3  
D = 192.168.0.4  
E = 192.168.0.5  
F = 192.168.0.6  

## Results  
Results of the computation time of the Dijkstra's algorithm. (time in seconds)

### Version 1.0 (easiest algorithm)  
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
