# monitor data on a bluetooth ble device.

import asyncio
from bleak import BleakScanner
from bleak import BleakClient

def notification_handler(sender, data):
    """
    Callback function that runs every time the device sends new data.
    'sender' is the characteristic handle.
    'data' is a bytearray.
    """
    del sender  # Unused variable
    print(data.decode('utf-8'), end='')

async def monitor(device):
    async with BleakClient(device.address) as client: # everything is running on a single thread.
        if client.is_connected:
            print(f"Connected to {device.name}, uuid={device.address}")
            for service in client.services:
                for characteristic in service.characteristics:
                    if 'notify' in characteristic.properties:
                        # Subscribe to the device's notifications.
                        await client.start_notify(characteristic.uuid, notification_handler)
        # Keep the connection open.
        while client.is_connected:
            # asyncio, is non-blocking, and allows the event loop to respond to incoming message events.
            await asyncio.sleep(1.0)

async def main():
    # Bluetooth LE scanner.
    devices = await BleakScanner.discover()
    # TODO: (josejimenezjr) - Swap this with an interactive prompt or flags.
    bluetooth_device = None
    for device in devices:
        if device.name == 'DSD TECH':
            bluetooth_device = device
    print(f'bluetooth_device: {bluetooth_device}')

    await monitor(bluetooth_device)

if __name__ == '__main__':
    try:
        asyncio.run(main())  # creates and runs the event loop.
    except KeyboardInterrupt:
        print('\n\nAbort.')