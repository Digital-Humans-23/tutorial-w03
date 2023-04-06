# Tutorial W03 - Settings things up

## Getting started (GPU version)
### Login to the cluster
  ```sh 
  $ ssh –Y USERNAME@euler.ethz.ch
  ```
### Setup git
- Generate ssh key
  ```sh 
  $ ssh-keygen -t ed25519  
  ```
- Print your public key  
  ```sh
  $ cat ./ssh/id_ed25519.pub
  ```
- Copy the public key to Github as done in tutorial 0.

- Login
  ```sh
  $ ssh -T git@github.com
  ```
- Clone repo:
  ```sh
  $ git clone git@github.com:Digital-Humans-23/tutorial-w03.git
  # Navigate to repo folder
  $ cd <Path to repo> # e.g: cd tutorial-w03 
  # checkout gpu branch
  $ git checkout gpu
  ```

### Check disk space
- Check the amount of disk space available in your account using the command `lquota`. Your jobs will crash if you dont have enough disk space to write the log files to disk.
  ```sh
  $ lquota
  ```
- The output should look something like this:
  ```sh
  +-----------------------------+-------------+------------------+------------------+------------------+
  | Storage location:           | Quota type: | Used:            | Soft quota:      | Hard quota:      |
  +-----------------------------+-------------+------------------+------------------+------------------+
  | /cluster/home/mimora        | space       |          6.66 GB |         17.18 GB |         21.47 GB |
  | /cluster/home/mimora        | files       |            16822 |           160000 |           200000 |
  +-----------------------------+-------------+------------------+------------------+------------------+
  | /cluster/shadow             | space       |               0B |          2.15 GB |          2.15 GB |
  | /cluster/shadow             | files       |                3 |            50000 |            50000 |
  +-----------------------------+-------------+------------------+------------------+------------------+
  | /cluster/scratch/mimora     | space       |          4.10 kB |          2.50 TB |          2.70 TB |
  | /cluster/scratch/mimora     | files       |                1 |          1000000 |          1500000 |
  +-----------------------------+-------------+------------------+------------------+------------------+
  ```

### Setup virtual environment (Linux / Cluster instructions):
- Load python3 for GPU
  ```sh
  $ env2lmod
  $ module load gcc/8.2.0 python_gpu/3.10.4
  ```
- Create and source a virtual environment
  ```sh
  # Navigate to home folder
  $ cd
  $ mkdir venvs && cd venvs
  $ python3 -m venv simpleEnvGpu
  $ source $HOME/venvs/simpleEnvGpu/bin/activate  
  # Update pip
  $ python3 -m pip install --upgrade pip
  ```
- Install requirements
  ```sh
  # Navigate to repo folder
  $ cd <Path to repo>  
  $ pip3 install -r requirements.txt

### Run jobs on server

- Run job
  ```sh
  # Before you start a job, make sure to run the following two commands, every time you start a new ssh connection to Euler.
  $ env2lmod
  $ module load gcc/8.2.0 python/3.9.9
  # Submit job
  $ sbatch ./jobs/gpu_job   
  ```
- Monitor job
  ```sh
  $ watch -n 1 squeue
  # Press Ctrl+C to stop monitoring the job 
  ```
- Check that job was run successfully 
  ```sh
  $ cat ./jobs/gpu_job.out    
  ```
  It should print something like: 
  ```sh
  torch.cuda.is_available(): True
  Using device: cuda
  
  torch.cuda.device_count(): 1
  torch.cuda.current_device(): 0
  torch.cuda.device(0): <torch.cuda.device object at 0x2b56cc2e32b0>
  torch.cuda.get_device_name(0): NVIDIA GeForce RTX 2080 Ti
  
  Creating GPU variable
  A: tensor([[0.1398, 0.0801, 0.7620,  ..., 0.9979, 0.8191, 0.1356],
  [0.9617, 0.1811, 0.4770,  ..., 0.5575, 0.3186, 0.6578],
  [0.6155, 0.6620, 0.4935,  ..., 0.9821, 0.9492, 0.9966],
  ...,
  [0.7402, 0.4816, 0.0675,  ..., 0.4227, 0.4904, 0.7470],
  [0.9830, 0.7237, 0.2267,  ..., 0.5317, 0.0089, 0.0513],
  [0.9697, 0.3609, 0.0698,  ..., 0.6418, 0.3757, 0.3971]],
  device='cuda:0')
  
  Memory Usage:
  Allocated: 0.4 GB
  Cached:    0.4 GB
  Done 
  ```
