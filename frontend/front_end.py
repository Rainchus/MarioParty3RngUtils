import tkinter as tk
from tkinter import ttk
from PIL import Image, ImageTk
import math
from space_positions import spaces
import os
import subprocess
import tkinter.simpledialog  # Add this import at the beginning of your file


# Board: 1
# StartSpace: 0x23
# NextSpace: 0x24
# EndSpace: 0x17
# Star: 0x1e
# P2 Space: 0x25
# P3 Space: 0x2c
# P4 Space: 0x25
# Items: -1, -1, -1
# Roll: 3

CLICKS = 0
player_items = []
arg_text = ['--item_space', '--hidden_block']

# Paths to images (replace with your actual file paths)
background_image_paths = {
    "Chilly Waters": "images/Boards/mp3_cw - Copy.png",
    "Deep Blooper Sea": "images/Boards/mp3_dbs - Copy.png",
    "Spiny Desert": "images/Boards/mp3_sd - Copy.png",
    "Woody Woods": "images/Boards/mp3_ww - Copy.png",
    "Creepy Cavern": "images/Boards/mp3_cc - Copy.png",
    "Waluigi's Island": "images/Boards/mp3_wi - Copy.png",
}

character_image_paths = [
    "images/Characters/46.0.png", "images/Characters/47.0.png", "images/Characters/48.0.png", "images/Characters/49.0.png",
    "images/Characters/50.0.png", "images/Characters/51.0.png", "images/Characters/52.0.png", "images/Characters/53.0.png"
]

item_image_paths = [
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
    "images/Items/93.0.png",
    "images/Items/94.0.png",
    "images/Items/95.0.png",
    "images/Items/96.0.png",
    "images/Items/97.0.png",
]

ItemStrings = [
    "Mushroom",
    "Skeleton Key",
    "Poison Mushroom",
    "Reverse Mushroom",
    "Cellular Shopper",
    "Warp Block",
    "Plunder Chest",
    "Bowser Phone",
    "Dueling Glove",
    "Lucky Lamp",
    "Golden Mushroom",
    "Boo Bell",
    "Boo Repellant",
    "Bowser Suit",
    "Magic Lamp",
    "Koopa Kard",
    "Barter Box",
    "Lucky Charm",
    "Wacky Watch",
    "None", #//19
]


def on_dropdown_change(event):
    global CLICKS
    global player_items

    # Get the selected value from the dropdown
    selected_option = dropdown.get()
    # Load the corresponding image
    load_image(background_image_paths[selected_option])
    os.system('cls')
    print(f"In mode {arg_text[second_dropdown.current()]}")
    if second_dropdown.current() == 0:
        print("Select Current Star Space:")
    else:
        print("Select Current Star Space:")
    CLICKS = 0
    player_items.clear()

def on_second_dropdown_change(event):
    global CLICKS
    global player_items

    # Get the selected value from the dropdown
    selected_option = dropdown.get()
    # Load the corresponding image
    load_image(background_image_paths[selected_option])
    os.system('cls')
    print(f"In mode {arg_text[second_dropdown.current()]}")
    print("Select Current Star Space:")
    CLICKS = 0
    player_items.clear()
    
def on_small_image_click(event, index):
    global CLICKS
    global player_items

    if CLICKS == 4:
        #convert no item grid index to in game value of no item
        if index == 19:
            index = -1
        player_items.append(index)
        print(f"{ItemStrings[index]}\n")
        print("P1 Item 2")
        CLICKS += 1
    elif CLICKS == 5:
        #convert no item grid index to in game value of no item
        if index == 19:
            index = -1
        player_items.append(index)
        print(f"{ItemStrings[index]}\n")
        print("P1 Item 3")
        CLICKS += 1
    elif CLICKS == 6:
        #convert no item grid index to in game value of no item
        if index == 19:
            index = -1
        player_items.append(index)
        print(f"{ItemStrings[index]}\n")
        print("P2 Space")
        CLICKS += 1

def on_background_image_click(event):
    global CLICKS
    global player_items

    if CLICKS >= 11:
        return

    x, y = event.x, event.y
    min_distance = float('inf')
    nearest_space = None
    cur_spaces = spaces[dropdown.current()]

    for space in cur_spaces:
        distance = math.sqrt((space.x - x) ** 2 + (space.y - y) ** 2)
        if distance < min_distance:
            min_distance = distance
            nearest_space = space

    if CLICKS == 0:
        with open("input.txt", "w") as file:
            file.write(f"Board: {dropdown.current()}\n")
            file.write(f"Star: {hex(nearest_space.value)}\n")
        print(f"{hex(nearest_space.value)}\n")
        print("P1 Start Space:")
        CLICKS += 1
    elif CLICKS == 1:
        with open("input.txt", "a") as file:
            file.write(f"StartSpace: {hex(nearest_space.value)}\n")
        print(f"{hex(nearest_space.value)}\n")
        print("P1 Next Space:")
        CLICKS += 1
    elif CLICKS == 2:
        with open("input.txt", "a") as file:
            file.write(f"NextSpace: {hex(nearest_space.value)}\n")
        print(f"{hex(nearest_space.value)}\n")
        print("P1 End Space:")
        CLICKS += 1
    elif CLICKS == 3:
        with open("input.txt", "a") as file:
            file.write(f"EndSpace: {hex(nearest_space.value)}\n")
        print(f"{hex(nearest_space.value)}\n")
        CLICKS += 1
        while True:
            print("Enter roll needed to reach end space")
            user_input = tkinter.simpledialog.askinteger("Input", "Enter roll needed to reach space:", minvalue=1, maxvalue=10)
            if user_input is not None:
                break
            else:
                print("Invalid input. Please enter a number between 1 and 10.")
        with open("input.txt", "a") as file:
            file.write(f"Roll: {user_input}\n")
        print("P1 Item 1")
    # elif CLICKS == 4:
    #     print("P1 Item 1")
    # elif CLICKS == 5:
    #     print("P1 Item 2")
    # elif CLICKS == 6:
    #     print("P1 Item 3")
    elif CLICKS == 7:
        with open("input.txt", "a") as file:
            file.write(f"P2 Space: {hex(nearest_space.value)}\n")
        print(f"{hex(nearest_space.value)}\n")
        print("P3 Space")
        CLICKS += 1
    elif CLICKS == 8:
        with open("input.txt", "a") as file:
            file.write(f"P3 Space: {hex(nearest_space.value)}\n")
        print(f"{hex(nearest_space.value)}\n")
        print("P4 Space")
        CLICKS += 1
    elif CLICKS == 9:
        with open("input.txt", "a") as file:
            file.write(f"P4 Space: {hex(nearest_space.value)}\n")
            print(f"{hex(nearest_space.value)}\n")
        # Write to file
        with open("input.txt", "a") as file:
            formatted_items = f"Items: {', '.join(map(str, player_items))}"
            file.write(f"{formatted_items}\n")
        if second_dropdown.current() == 0:
            result = subprocess.run(['mp3_rng_util.exe',  '--item_space'], capture_output=True, text=True)
        else:
            result = subprocess.run(['mp3_rng_util.exe',  '--hidden_block'], capture_output=True, text=True)
        print(result.stdout)  # Print the output from the executable
        print(result.stderr)  # Print any errors from the executable
        CLICKS += 1

def load_image(image_path):
    image = Image.open(image_path)
    image = image.resize((1152, 864), Image.LANCZOS)  # Resize the image
    photo = ImageTk.PhotoImage(image)
    label_image.config(image=photo)
    label_image.image = photo  # Keep a reference to avoid garbage collection

def load_small_images():
    small_image_size = (32, 32)
    small_images = []
    
    for path in item_image_paths:
        image = Image.open(path)
        image = image.resize(small_image_size, Image.LANCZOS)
        photo = ImageTk.PhotoImage(image)
        small_images.append(photo)
    
    return small_images

# Create the main window
root = tk.Tk()
root.title("Mario Party 3 Wacky Watch Manip")

# Dropdown (Combobox) to select an image
dropdown = ttk.Combobox(root, values=list(background_image_paths.keys()))
dropdown.current(0)  # Set default selection
dropdown.pack()

# Bind the dropdown change event
dropdown.bind("<<ComboboxSelected>>", on_dropdown_change)


#TODO: implement actual functionality of Item Space/ Hidden Block Toggle
# Add a second dropdown (Combobox) below the first one with 2 options
second_dropdown = ttk.Combobox(root, values=["Item Space", "Hidden Block"])
second_dropdown.current(0)  # Set default selection
second_dropdown.pack()
second_dropdown.bind("<<ComboboxSelected>>", on_second_dropdown_change)

# Create a frame to hold the 4x2 grid of small images
frame_small_images = tk.Frame(root)
frame_small_images.pack()

# Load small images and add them to the grid with click binding
small_images = load_small_images()
for i, photo in enumerate(small_images):
    row = i // 8
    col = i % 8
    label = tk.Label(frame_small_images, image=photo)
    label.grid(row=row, column=col, padx=0, pady=0)
    label.bind("<Button-1>", lambda event, idx=i: on_small_image_click(event, idx))

# Create a label to display the main image
label_image = tk.Label(root)
label_image.pack()

# Load the initial image
load_image(background_image_paths[dropdown.get()])

# Bind the click event to the label
label_image.bind("<Button-1>", on_background_image_click)

print("Select Current Star Space:")
# Start the Tkinter main loop
root.mainloop()
