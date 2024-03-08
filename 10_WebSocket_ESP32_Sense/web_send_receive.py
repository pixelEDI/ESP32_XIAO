import asyncio
import websockets

async def main():
    async with websockets.connect("wss://nodered.ipv64.net/esp32") as websocket:
        await websocket.send("Was sagt ein Linux-Admin, wenn er einen Burger bestellt?")
        message = await websocket.recv()
        print(f"Nachricht vom Server: {message}")
asyncio.run(main())
