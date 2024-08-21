def prepend_hex_to_lines(input_file, output_file):
    with open(input_file, 'r') as infile, open(output_file, 'w') as outfile:
        for i, line in enumerate(infile):
            hex_count = f"0x{i:03X}"
            outfile.write(f"/* {hex_count} */ {line}")

# Example usage:
input_file = 'temp.txt'
output_file = 'output.txt'
prepend_hex_to_lines(input_file, output_file)
