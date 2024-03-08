import asyncio
import websockets

async def main():
    async with websockets.connect("wss://nodered.ipv64.net/esp32") as websocket:
        await websocket.send("Ich mag Websockets")
        # Keine Empfangsaktion mehr hier

asyncio.run(main())
