import tkinter as tk
from tkinter import ttk
from PIL import Image, ImageTk
import math
from space_positions import spaces

CLICKS = 0

InputDict = {
    "Select Player 1 Start Space:": "StartSpace:",
    "Select Player 1 End Space:": "EndSpace:",
    "Select Current Star Space:": "Star:",
    "Select Player 2 Start Space:": "P2 Space:",
    "Select Player 3 Start Space:": "P3 Space:",
    "Select Player 4 Start Space:": "P4 Space:",
}

def load_image(image_path):
    image = Image.open(image_path)
    image = image.resize((1152, 864), Image.LANCZOS)  # Resize the image
    photo = ImageTk.PhotoImage(image)
    label_image.config(image=photo)
    label_image.image = photo  # Keep a reference to avoid garbage collection

def load_small_images():
    small_image_size = (16, 16)
    small_images = []
    
    for path in small_image_items_paths:
        image = Image.open(path)
        image = image.resize(small_image_size, Image.LANCZOS)
        photo = ImageTk.PhotoImage(image)
        small_images.append(photo)
    
    return small_images

def translate_3d_to_2d(X, Z, scale_x, scale_y, offset_x, offset_y):
    x_2d = scale_x * X + offset_x
    y_2d = scale_y * Z + offset_y
    return x_2d, y_2d

def temp():
    # Refined scale factors and offsets
    scale_x, scale_y = 1.46797, 1.11143  # Updated based on previous calculation
    offset_x, offset_y = 593.37, 445.04  # These can be fine-tuned

    # 3D coordinates from the game
    X, Z = -240, -160

    # Translate to 2D
    x, y = translate_3d_to_2d(X, Z, scale_x, scale_y, offset_x, offset_y)
    print(f"2D coordinates on the image: ({x:.2f}, {y:.2f})")

# List of dictionary keys
input_keys = list(InputDict.keys())

def print_colored(text, color_code):
    # Print the text with the specified color code
    print(f"{color_code}{text}\033[0m")

def on_click(event):
    # global CLICKS

    # x, y = event.x, event.y
    # print(f"Space({x}, {y}, {CLICKS}),")
    # CLICKS += 1



    global CLICKS
    x, y = event.x, event.y
    min_distance = float('inf')
    nearest_space = None
    cur_spaces = spaces[dropdown.current()]

    for space in cur_spaces:
        distance = math.sqrt((space.x - x) ** 2 + (space.y - y) ** 2)
        if distance < min_distance:
            min_distance = distance
            nearest_space = space

    if nearest_space is not None:
        if CLICKS == 0:
            with open('input.txt', 'w') as file:
                file.write(f"Board: {dropdown.current()}\n")
        # Get the key from the dictionary based on the CLICKS index
        key = input_keys[CLICKS]
        value = InputDict[key]
        
        # Write to file
        with open("input.txt", "a") as file:
            file.write(f"{value} {hex(nearest_space.value)}\n")

        # Increment CLICKS and reset if necessary
        CLICKS += 1
        if CLICKS >= len(input_keys):
            CLICKS = 0

        #print(f"Clicked at: ({x}, {y}), Nearest space: ({nearest_space.x}, {nearest_space.y}), Value: {hex(nearest_space.value)}")
        print_colored(f"Space Selected: {hex(nearest_space.value)} ({nearest_space.value})\n", "\033[36m")
        print(f"\033[32m{input_keys[CLICKS]}\033[0m")
        

def on_dropdown_change(event):
    global CLICKS

    # Get the selected value from the dropdown
    selected_option = dropdown.get()
    # Load the corresponding image
    load_image(image_paths[selected_option])
    CLICKS = 0

# Create the main window
root = tk.Tk()
root.title("Mario Party 3 Wacky Watch Manip")

# Paths to images (replace with your actual file paths)
image_paths = {
    "Chilly Waters": "images/Boards/mp3_cw - Copy.png",
    "Deep Blooper Sea": "images/Boards/mp3_dbs - Copy.png",
    "Spiny Desert": "images/Boards/mp3_sd - Copy.png",
    "Woody Woods": "images/Boards/mp3_ww - Copy.png",
    "Creepy Cavern": "images/Boards/mp3_cc - Copy.png",
    "Waluigi's Island": "images/Boards/mp3_wi - Copy.png",
}

# small_image_paths_characters = [
#     "images/Characters/46.0.png", "images/Characters/47.0.png", "images/Characters/48.0.png", "images/Characters/49.0.png",
#     "images/Characters/50.0.png", "images/Characters/51.0.png", "images/Characters/52.0.png", "images/Characters/53.0.png"
# ]

small_image_items_paths = [
    "images/Items/77.0.png",
    "images/Items/78.0.png",
    "images/Items/79.0.png",
    "images/Items/80.0.png",
    "images/Items/81.0.png",
    "images/Items/82.0.png",
    "images/Items/83.0.png",
    "images/Items/84.0.png",
    "images/Items/85.0.png",
    "images/Items/86.0.png",
    "images/Items/87.0.png",
    "images/Items/88.0.png",
    "images/Items/89.0.png",
    "images/Items/90.0.png",
    "images/Items/91.0.png",
    "images/Items/92.0.png",
    "images/Items/93.0.png",
    "images/Items/94.0.png",
    "images/Items/95.0.png",
    "images/Items/96.0.png",
]

# Dropdown (Combobox) to select an image
dropdown = ttk.Combobox(root, values=list(image_paths.keys()))
dropdown.current(0)  # Set default selection
dropdown.pack()

# Bind the dropdown change event
dropdown.bind("<<ComboboxSelected>>", on_dropdown_change)

# Create a frame to hold the 4x2 grid of small images
frame_small_images = tk.Frame(root)
frame_small_images.pack()

# # Load small images and add them to the grid
small_images = load_small_images()
for i, photo in enumerate(small_images):
    row = i // 8
    col = i % 8
    label = tk.Label(frame_small_images, image=photo)
    label.grid(row=row, column=col, padx=5, pady=5)

# Create a label to display the main image
label_image = tk.Label(root)
label_image.pack()

# Load the initial image
load_image(image_paths[dropdown.get()])

# Bind the click event to the label
label_image.bind("<Button-1>", on_click)

# # Test translation (can be removed if unnecessary)
# temp()

# Start the Tkinter main loop
print(f"\033[32m{input_keys[CLICKS]}\033[36m")
root.mainloop()
