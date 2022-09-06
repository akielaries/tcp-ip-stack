/*
 **Very beginning of this project**
 * Goal is to implement an TCP/IP stack and learn the ins and out
 * of network and systems program along with the core principles
 * of the discipline.
 *
 *
 * This file begins with some implementation of TUN/TAP
 *      TUN : TUN(nel); simulates layer 3 - Network. Carries IP packets
 *      TAP : simulates layer 2 - Data Link. Responsible for transport of 
 *      ethernet frames. Can be implemented for user space network bridge.
 *      ** tunneling : wrapping packets inside payload of other packets **
 *
 * In common *nix systems, implementatoin of TUN/TAP interface allows for
 * userspace networking, i.e. userspace applications are able to view and 
 * manipulate network straffic on the ethernet or IP lvl.
 * In this particular setting, we will start from layer 2 and up as our
 * physical layer is previously established.
 *
 */


// instantiate TAP device
static int tun_alloc(char *dev) {
    // document this in next pushes for better understanding
    struct ifreq ifr;
    int fd, err;

    if ((fd = open("dev/net/tap")))

}


