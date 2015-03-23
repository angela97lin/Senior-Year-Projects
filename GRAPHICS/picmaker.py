#Work 0: Imagine all the pixels...
#Creating a computer-generated image!
import random, math

i_width = 600;
i_height = 600;
max_color = 255;

#creates a picture with randomly colored pixels (with max red value to give the pixels a reddish hue)!
def rand_maker():
    f = open("rand.ppm", "w")
    header = "P3 %d %d %d \n" % (i_width, i_height, max_color)
    #print header
    f.write(header)
    for x in range(i_width):
        for y in range(i_height):
            red_val = random.randint(0, 255)
            blue_val = random.randint(0, 255)
            green_val = random.randint(0, 255)
            color = "%d %d %d " % (red_val, green_val, blue_val)
            f.write(color)
        f.write("\n")
    f.close()

#makes black swirly image
def swirl_maker():
    f = open("swirl.ppm", "w")
    header = "P3 %d %d %d \n" % (i_width, i_height, max_color)
    #print header
    f.write(header)
    freq = 1
    for x in range(i_width):
        freq = freq + .05
        for y in range(i_height):
            red_val = abs(math.sin(freq * y)) * 100
            blue_val = abs(math.sin(freq * y)) * 100
            green_val = abs(math.sin(freq * y)) * 100
            color = "%d %d %d " % (red_val, green_val, blue_val)
            f.write(color)
        f.write("\n")
    f.close()

#makes a fadey-rainbow image
def rainbow_maker():
    f = open("rainbow.ppm", "w")
    header = "P3 %d %d %d \n" % (i_width, i_height, max_color)
    #print header
    f.write(header)
    freq = .0085
    for x in range(i_width):
        #freq = freq + .055 #for swirls
        for y in range(i_height):
            red_val = abs(math.sin(freq * y)) * 127 + 128
            blue_val = abs(math.sin(freq * y +  2*(math.pi/3))) * 127 + 128
            green_val = abs(math.sin(freq * y +  4*(math.pi/3))) * 127 + 128
            color = "%d %d %d " % (red_val, green_val, blue_val)
            f.write(color)
        f.write("\n")
    f.close()

if __name__ == "__main__":
    #rand_maker()
    swirl_maker()
    rainbow_maker()
