#!/usr/bin/env python3
# spool up a dbus server on the nstack container bus
import os
import sys
# import argparse

from gi.repository import GLib
from pydbus import SessionBus


class TestObject:
    name = "com.nstack.DbusTest"

    dbus = """
    <node>
      <interface name='com.nstack.DbusTest'>
        <method name='Ping'>
          <arg type='ay' name='input' direction='in'/>
          <arg type='d' name='output' direction='out'/>
        </method>
      </interface>
    </node>
    """

    def __init__(self):
        pass

    def Ping(self, data):
        size = len(data) / 1000000
        print("PING: data size (MB) - {0:.2f}".format(size))
        return size


def main():
    # parser = argparse.ArgumentParser()
    # setup the main loop
    loop = GLib.MainLoop()
    # publish on dbus and start main loop
    try:
        with SessionBus().publish(TestObject.name, TestObject()):
            print("Server running on {}".format(os.environ['DBUS_SESSION_BUS_ADDRESS']))
            loop.run()
    except KeyboardInterrupt:
        loop.quit()

    return 0


if __name__ == '__main__':
    # set dbus bus path
    # os.environ['DBUS_SESSION_BUS_ADDRESS'] = 'unix:path=/var/run/nstack/container-dbus.sock'
    sys.exit(main())
