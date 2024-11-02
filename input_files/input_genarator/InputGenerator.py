import os

def read_sensor_data_and_commands_from_txt(file_path):
    sensor1_data = []
    sensor2_data = []
    commands = []
    
    with open(file_path, 'r') as file:
        for line in file:
            parts = line.strip().split()
            if len(parts) >= 3:
                try:
                    sensor1 = float(parts[0])
                    sensor2 = float(parts[1])
                    command = parts[2]
                    sensor1_data.append(sensor1)
                    sensor2_data.append(sensor2)
                    commands.append(command)
                except ValueError:
                    continue
    return sensor1_data, sensor2_data, commands

def collect_all_sensor_data_and_commands():
    all_sensor1_data = []
    all_sensor2_data = []
    all_commands = []
    current_directory = os.getcwd()

    for filename in os.listdir(current_directory):
        if filename.endswith(".txt"):
            file_path = os.path.join(current_directory, filename)
            sensor1_data, sensor2_data, commands = read_sensor_data_and_commands_from_txt(file_path)
            all_sensor1_data.extend(sensor1_data)
            all_sensor2_data.extend(sensor2_data)
            all_commands.extend(commands)

    return all_sensor1_data, all_sensor2_data, all_commands

def write_sensor_data_to_file(filename, sensor1_data, sensor2_data):
    with open(filename, 'w') as f:
        for s1, s2 in zip(sensor1_data, sensor2_data):
            f.write(f"{s1} {s2}\n")

def write_data_to_file(filename, data):
    with open(filename, 'w') as f:
        for item in data:
            f.write(f"{item}\n")

sensor1_vector, sensor2_vector, commands_vector = collect_all_sensor_data_and_commands()
write_sensor_data_to_file('Input1_Sensors.txt', sensor1_vector, sensor2_vector)
write_data_to_file('Input2_Commands.txt', commands_vector)
