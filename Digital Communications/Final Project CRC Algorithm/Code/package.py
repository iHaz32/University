import random

class Package:
    def __init__(self, D, P):
        self.D = D
        self.P = P
        self.k = len(D)
        self.n = len(D) + len(P) - 1

    def send(self):
        self.calculateF()
        self.calculateT()
        self.errors()
        self.calculateRes()
    

    def calculateF(self):
        expandedD = self.D;
        for i in range(self.n - self.k):
            expandedD += '0'
        self.F = self.binary_division(expandedD, self.P)
        if (len(self.F) < self.n - self.k):
            for i in range(self.n - self.k - len(self.F)):
                self.F = '0' + self.F
        

    def calculateT(self):
        self.T = self.D + self.F

    def errors(self):
        oldT = self.T
        for i in range(len(self.T)):
            randomNumber = random.randint(0, 999)
            if randomNumber == 0:
                if self.T[i] == '0':
                    self.T = self.T[:i] + '1' + self.T[i+1:]
                else:
                    self.T = self.T[:i] + '0' + self.T[i+1:]
        if (oldT == self.T):
            self.isDiff = False
        else:
            self.isDiff = True

    def calculateRes(self):
        self.res = self.binary_division(self.T, self.P)

    def xor(self, a, b): 
  
        # initialize result 
        result = [] 
    
        # Traverse all bits, if bits are 
        # same, then XOR is 0, else 1 
        for i in range(1, len(b)): 
            if a[i] == b[i]: 
                result.append('0') 
            else: 
                result.append('1') 
    
        return ''.join(result) 

    def binary_division(self, dividend, divisor): 
  
        # Number of bits to be XORed at a time. 
        pick = len(divisor) 
    
        # Slicing the dividend to appropriate 
        # length for particular step 
        tmp = dividend[0: pick] 
    
        while pick < len(dividend): 
    
            if tmp[0] == '1': 
    
                # replace the dividend by the result 
                # of XOR and pull 1 bit down 
                tmp = self.xor(divisor, tmp) + dividend[pick] 
    
            else:   # If leftmost bit is '0' 
                # If the leftmost bit of the dividend (or the 
                # part used in each step) is 0, the step cannot 
                # use the regular divisor; we need to use an 
                # all-0s divisor. 
                tmp = self.xor('0'*pick, tmp) + dividend[pick] 
    
            # increment pick to move further 
            pick += 1
    
        # For the last n bits, we have to carry it out 
        # normally as increased value of pick will cause 
        # Index Out of Bounds. 
        if tmp[0] == '1': 
            tmp = self.xor(divisor, tmp) 
        else: 
            tmp = self.xor('0'*pick, tmp) 
    
        R = tmp 
        return R 