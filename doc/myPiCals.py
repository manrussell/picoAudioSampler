
# sample rate 44100Hz
# = 0.000,022,68 == 22.7 micro seconds
sample_rate=44100
print("sample rate=",  sample_rate)
fs=1/sample_rate

suppressedNum=f"{fs:.8f}"
print(suppressedNum)


sample_rate=22050
fs=1/sample_rate
print("sample rate=",  sample_rate)
suppressedNum=f"{fs:.8f}"
print(suppressedNum)
