#!/usr/bin/env python3

# spool up a dbus server on the nstack container bus
import os
import sys
import argparse

from gi.repository import GLib
from pydbus import SessionBus


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('param', type=int, help="Size in bytes to send to server")
    args = parser.parse_args()

    bus = SessionBus()

    server_proxy = bus.get('com.nstack.DbusTest')

    print("Sending ping - {}".format(args.param))
    output = server_proxy.Ping(bytes(args.param))
    print("Received pong - {}".format(output))

    return 0


if __name__ == '__main__':
    # set dbus bus path
    # os.environ['DBUS_SESSION_BUS_ADDRESS'] = 'unix:path=/var/run/nstack/container-dbus.sock'
    sys.exit(main())
