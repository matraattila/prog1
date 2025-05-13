import math
import sys

class Csomopont:
    def __init__(self, betu='/'):
        self.betu = betu
        self.balNulla = None
        self.jobbEgy = None

class LZWBinFa:
    def __init__(self):
        self.gyoker = Csomopont()
        self.fa = self.gyoker
        self.melyseg = 0
        self.maxMelyseg = 0
        self.atlagOsszeg = 0
        self.atlagDb = 0
        self.szorasOsszeg = 0.0
        self.atlag = 0.0

    def insert_character(self, b):
        if b == '0':
            if not self.fa.balNulla:
                self.fa.balNulla = Csomopont('0')
                self.fa = self.gyoker
            else:
                self.fa = self.fa.balNulla
        else:
            if not self.fa.jobbEgy:
                self.fa.jobbEgy = Csomopont('1')
                self.fa = self.gyoker
            else:
                self.fa = self.fa.jobbEgy

    def print_tree(self):
        self.melyseg = 0
        self._print_node(self.gyoker)

    def _print_node(self, node):
        if node:
            self.melyseg += 1
            self._print_node(node.jobbEgy)
            print("---" * self.melyseg + f"{node.betu}({self.melyseg - 1})")
            self._print_node(node.balNulla)
            self.melyseg -= 1

    def get_depth(self):
        self.melyseg = 0
        self.maxMelyseg = 0
        self._calculate_depth(self.gyoker)
        return self.maxMelyseg - 1

    def _calculate_depth(self, node):
        if node:
            self.melyseg += 1
            if self.melyseg > self.maxMelyseg:
                self.maxMelyseg = self.melyseg
            self._calculate_depth(node.jobbEgy)
            self._calculate_depth(node.balNulla)
            self.melyseg -= 1

    def get_mean(self):
        self.melyseg = 0
        self.atlagOsszeg = 0
        self.atlagDb = 0
        self._calculate_mean(self.gyoker)
        self.atlag = self.atlagOsszeg / self.atlagDb
        return self.atlag

    def _calculate_mean(self, node):
        if node:
            self.melyseg += 1
            self._calculate_mean(node.jobbEgy)
            self._calculate_mean(node.balNulla)
            self.melyseg -= 1
            if not node.jobbEgy and not node.balNulla:
                self.atlagDb += 1
                self.atlagOsszeg += self.melyseg

    def get_variance(self):
        self.atlag = self.get_mean()
        self.szorasOsszeg = 0.0
        self.melyseg = 0
        self.atlagDb = 0
        self._calculate_variance(self.gyoker)
        if self.atlagDb - 1 > 0:
            return math.sqrt(self.szorasOsszeg / (self.atlagDb - 1))
        else:
            return math.sqrt(self.szorasOsszeg)

    def _calculate_variance(self, node):
        if node:
            self.melyseg += 1
            self._calculate_variance(node.jobbEgy)
            self._calculate_variance(node.balNulla)
            self.melyseg -= 1
            if not node.jobbEgy and not node.balNulla:
                self.atlagDb += 1
                self.szorasOsszeg += (self.melyseg - self.atlag) ** 2

def usage():
    print("Usage: python lzwtree.py in_file -o out_file")

def main():
    if len(sys.argv) != 4:
        usage()
        return -1

    in_file = sys.argv[1]
    if sys.argv[2] != "-o":
        usage()
        return -2

    out_file = sys.argv[3]

    try:
        with open(in_file, "rb") as be_file:
            data = be_file.read()
    except FileNotFoundError:
        print(f"{in_file} does not exist...")
        usage()
        return -3

    bin_fa = LZWBinFa()
    in_comment = False

    for b in data:
        if b == ord('>'):
            in_comment = True
            continue
        if b == ord('\n'):
            in_comment = False
            continue
        if in_comment or b == ord('N'):
            continue

        for i in range(8):
            if b & 0x80:
                bin_fa.insert_character('1')
            else:
                bin_fa.insert_character('0')
            b <<= 1

    with open(out_file, "w") as ki_file:
        bin_fa.print_tree()
        ki_file.write(f"depth = {bin_fa.get_depth()}\n")
        ki_file.write(f"mean = {bin_fa.get_mean():.2f}\n")
        ki_file.write(f"var = {bin_fa.get_variance():.2f}\n")

if __name__ == "__main__":
    main()
