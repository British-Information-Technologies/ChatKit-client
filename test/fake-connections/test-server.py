# Credit: https://www.geeksforgeeks.org/python-binding-and-listening-with-sockets/

import socket
import sys
import asyncio

# make sure lists are only ever length = 2
connections = []

async def handle(conn, address, index):
    other_client = connections[(index + 1) % 2]
    
    while(True):
        data = conn.recv(1024)
        
        print(address[0] + ' recv: ' + data.decode())

        other_client.sendall(data)

        await asyncio.sleep(1)

        




async def main():
    # specify Host and Port
    HOST = ''
    PORT = 5790
    
    soc = socket.socket(
        socket.AF_INET,         # append 6 for ipv6 or remove for ipv4
        socket.SOCK_STREAM
    )
    
    try:
        # With the help of bind() function
        # binding host and port
        soc.bind((HOST, PORT))
        
    except socket.error as message: 
        # if any error occurs then with the
        # help of sys.exit() exit from the program
        print(
            'Bind failed. Error Code : ' +
            str(message[0]) +
            ' Message ' + 
            message[1]
        )
        
        sys.exit()
        
    # print if Socket binding operation completed   
    print('Socket binding operation completed')
    
    # With the help of listening () function
    # starts listening
    soc.listen(9)

    conn, address = soc.accept()

    print('Connected with ' + address[0] + ':' + str(address[1]))

    task1 = asyncio.create_task(
        handle(conn, address, index=0)
    )

    connections.append(conn)

    conn, address = soc.accept()

    print('Connected with ' + address[0] + ':' + str(address[1]))

    task2 = asyncio.create_task(
        handle(conn, address, index=1)
    )

    connections.append(conn)

    await asyncio.gather(task1, task2)

    for conn in connections:
        conn.close()
    
    soc.close()




asyncio.run(main())