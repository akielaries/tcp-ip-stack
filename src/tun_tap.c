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
 *
 * Some notable sources:
 *      - https://www.rfc-editor.org/rfc/rfc7414
 *      - https://www.rfc-editor.org/rfc/rfc826
 *      - https://www.kernel.org/doc/Documentation/networking/tuntap.txt
 *
 */

#include <stdlib.h>
#include <string.h>
#include <errno.h>


/*
 *
 * instantiate TAP device
 * dev refers to our device name
 */
 static int tun_alloc(char *dev) {
    // document this in next pushes for better understanding
    struct ifreq ifr;
    int fd, err;

    if ((fd = open("dev/net/tap", O_RDWR)) < 0) {
        print_error("DBG STMT   ERR: UNABLE TO OPEN TUN/TAP dev");
        // exit the program
        exit(1);
    }

    CLEAN(ifr);
    
    /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
     *        IFF_TAP   - TAP device
     *
     *        IFF_NO_PI - Do not provide packet information
     */
    
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
    if(*dev) {
        strncpy(ifr.ifr_name, dev, IFNAMSIZ);
    }

    if ((err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0) {
        print_error("DBG STMT ERR: UNABLE TO ioctl TUN: %s\n", strerror(errno));
        close(fd);
        return err;
    }
    strcpy(dev, ifr.ifr_name);
    return fd;

}


