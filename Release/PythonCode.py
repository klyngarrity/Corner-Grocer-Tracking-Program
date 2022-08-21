import string
FILENAME = 'items.txt'
# This function reads line from a file and returns them in raw form
def readFile(filename):
    
    lines = None
    
    with open('items.txt') as file:
        lines = file.readlines()

    return lines;

# This function gets the inventory read from the file and returns keys the frequency of their values
def getInventory():
  
    inventory = {}
    
    items = readFile('items.txt')

    # Loop through the list of items, if item is not in the dictionary, add it. If it is, increase the value by one.
    for item in items:
     
        item = item.strip() 

        if item in inventory:
            inventory[item] += 1 
        else:
            inventory[item] = 1 

            
    return inventory;
    items.close()

 # This function loops through the dictionary's keys and values and outputs in the form key : value
def determineInventory():
    
    inventory = getInventory()

    for key, value in inventory.items():
        print (key, ":", value)

# This function returns the frequency of a specific requested item
def determineFrequency(item):

    inventory = getInventory()
    # Input will read whether caps or not
    item = item.capitalize()
    value = inventory[item]
    
    return value;
    
# This function loops through the dictionary of items, printes with just a space between, and writes them to the file
def output():
   
    inventory = getInventory()
    f = open("frequency.dat", "w")
 
    for key, value in inventory.items():
        f.write(str(key) + " " + str(value) + "\n")

    f.close()
