import posix_ipc
import time

class QueueHandler:
    def __init__(self, name):
        self.name = name
        self.mq = self._open_queue()
    
    def _open_queue(self):
        q_name = "/"
        q_name += self.name
        q_name += "_queue"
        return posix_ipc.MessageQueue(q_name)
    
    def put(self, message: any):
        self.mq.send(str(message))


if __name__ == "__main__":
    qh = QueueHandler("pytest")
    i = 0
    while True:
        sentence = "Message " + str(i) + " from python node"
        qh.put(str(sentence))
        i += 1
        time.sleep(1)
