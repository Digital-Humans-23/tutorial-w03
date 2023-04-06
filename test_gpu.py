import torch

# Check cuda availability
print("torch.cuda.is_available():", torch.cuda.is_available())

# setting device on GPU if available, else CPU
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
print('Using device:', device)

#Additional Info when using cuda
if device.type == 'cuda':
    print()
    print("torch.cuda.device_count():", torch.cuda.device_count())
    print("torch.cuda.current_device():", torch.cuda.current_device())
    print("torch.cuda.device(0):", torch.cuda.device(0))
    print("torch.cuda.get_device_name(0):", torch.cuda.get_device_name(0))

    print()
    print("Creating GPU variable")
    A = torch.rand(10000, 10000, device=device)
    print("A:", A)

    print()    
    print('Memory Usage:')
    print('Allocated:', round(torch.cuda.memory_allocated(0)/1024**3,1), 'GB')
    print('Cached:   ', round(torch.cuda.memory_reserved(0)/1024**3,1), 'GB')

print("Done")
