from enum import Enum
import sys


class State(Enum):
    SEARCHING = 0
    NEW_FRAME = 1
    BLANK = 2
    BIT = 3


frames = []

with open(sys.argv[1], encoding="utf8") as f:
    for line in f:
        if not line.startswith("RAW_Data"):
            continue

        line = line.replace("RAW_Data: ", "")
        raw = line.split(" ")
        raw = [int(i) for i in raw]
        state = State.SEARCHING
        frame = []
        for num in raw:
            if state == State.SEARCHING:
                frame = []
                if num < -450:
                    state = State.NEW_FRAME
            elif state == State.NEW_FRAME:
                if num > 450:
                    state = State.BLANK
                else:
                    state = State.SEARCHING
                    print("Expected frame start, got", num)
            elif state == State.BLANK:
                if num < -500:
                    state = State.NEW_FRAME
                    frames.append(frame)
                    frame = []
                elif num < 0:
                    state = State.BIT
                else:
                    state = State.SEARCHING
                    print("Expected blank, got", num)
            elif state == State.BIT:
                if num > 300:
                    frame.append(1)
                    state = State.BLANK
                elif num > 120:
                    frame.append(0)
                    state = State.BLANK
                else:
                    state = State.SEARCHING
                    print("Expected bit, got", num)

output = open("output.txt", "w", encoding="utf8")
packets = {}

for frame in frames:
    binary = "".join([str(i) for i in frame])
    if binary == "":
        continue
    hexs = f"{int(binary, 2):X}"
    if len(binary) == 48:
        hexs_c = [f"0x{hexs[i : i + 2]}" for i in range(0, len(hexs), 2)]
        hexs_c = "{" + ", ".join(hexs_c) + "},"
        # Check if hex is already in packets
        if hexs in packets:
            packets[hexs] += 1
        else:
            print(hexs)
            output.write(hexs_c + "\n")
            packets[hexs] = 1
