#!/usr/bin/python3

import tensorflow as tf
import time

current_time = time.localtime()
message = time.strftime("Message @ %d %b %Y %H:%M:%S", current_time)
with open("message.txt", "w") as f:
    f.write(message)

