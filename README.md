# Philosophers Project

## Description

<table>
  <tr>
    <td valign="top">
      <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/7/7b/An_illustration_of_the_dining_philosophers_problem.png/578px-An_illustration_of_the_dining_philosophers_problem.png" alt="Dining philosophers" />
    </td>
    <td>
      This project implements the dining philosophers problem using threads in C. The dining philosophers problem is a classic synchronization problem in computer science where a number of philosophers sit at a table with a bowl of spaghetti in front of each of them, and they must alternate between thinking and eating. However, they can only eat if they have both chopsticks (forks) available, and the chopsticks are shared between adjacent philosophers.
    </td>
  </tr>
</table>

## Requirements
- C compiler (e.g., GCC)
- POSIX threads library (pthread)

## Folder Structure
The project is structured into two parts:
- Mandatory part: Implemented with threads using mutexes. Located in the "philo/" folder.
- Bonus part: Implemented with processes using semaphores. Located in the "philo_bonus/" folder.

## How to Compile (Mandatory Part)
Navigate to the "philo/" folder and use the provided make file to compile the mandatory part:
```bash
cd philo/
make
```

## How to Compile (Bonus Part)
Navigate to the "philo_bonus/" folder and use the provided make file to compile the bonus part:

```bash
cd philo_bonus/
make
```

How to Run

Execute the compiled binary with the desired arguments
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
# for bonus use ./philo_bonus 
```
> The last argument is optional

Example :
```bash
./philo 5 800 200 200 7
```
This command runs the mandatory part with 5 philosophers, a time to die of 800 milliseconds, time to eat of 200 milliseconds, time to sleep of 200 milliseconds, and each philosopher must eat 7 times before the program ends.
