import posix_ipc
import time
import signal

class QueueHandler:
    def __init__(self, name):
        self.name = name
        self.mq = self._open_queue()
        self.stop_request = False
        signal.signal(signal.SIGINT, self._stop_signal_handler)

    def _open_queue(self):
        q_name = "/"
        q_name += self.name
        q_name += "_queue"
        return posix_ipc.MessageQueue(q_name)

    def _stop_signal_handler(self, *args):
        print("External pySensor stop received.")
        self.stop_request = True
        exit(0)

    def put(self, message: any):
        try:
            self.mq.send(str(message))
        except (posix_ipc.SignalError):
            pass


if __name__ == "__main__":
    qh = QueueHandler("pytest")
    i = 0
    while qh.stop_request == False:
        sentence = "Message " + str(i) + " from python node"
        qh.put(str(sentence))
        i += 1
        for x in range(1, 100000): # non-blocking sleep
            y = x + 2
