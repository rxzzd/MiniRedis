import socket
import time

def send_command(cmd_string):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:

        client_socket.connect(('127.0.0.1', 5555))

        client_socket.send(cmd_string.encode('utf-8'))

        response = client_socket.recv(1024)

        decoded_response = response.decode('utf-8')

        print(f'Ответ Сервера: {decoded_response}')
    except Exception as e:
        print(f"Ошибка сети: {e}")
    finally:
        client_socket.close()
        pass

if __name__ == "__main__":
    print("--- Команда записи SET ---")

    send_command("SET user_1 Dmitry 3")

    print("\n--- Моментальное чтение ключа ---")
    send_command("GET user_1")

    print("\n--- Ожидание 4 секунды ---")
    time.sleep(4)

    print("\n--- Попытка получить данные после истечния TTL")
    send_command("GET user_1")