#!/usr/bin/env python3
import sys
DATA="TLS-SEC"

import time
from pynput.keyboard import Key, Controller

keyboard = Controller()

num_state, maj_state = 0, 0

print("Press enter to start!")
input()
print("[+] starting to print")
for letter in DATA:
        print(f"[+] {letter} : ",end= "")
        letter_ascii = f"{ord(letter):08b}"
        for i in range(4):
                bit_num, bit_maj = (int(e) for e in letter_ascii[2*i:2*(i+1)])
                if num_state^bit_num:
                        keyboard.tap(Key.num_lock)
                if maj_state^bit_maj:
                        keyboard.tap(Key.caps_lock)

                maj_state = bit_maj
                num_state = bit_num
                print(f"{bit_num}{bit_maj}",end = "")
                sys.stdout.flush()
                

                time.sleep(2)

        print()
