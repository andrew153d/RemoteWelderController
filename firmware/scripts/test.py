from collections import deque
import base64

def image_to_base64(image_path):
    with open(image_path, "rb") as image_file:
        # Read the image file in binary mode
        image_binary = image_file.read()
        # Encode the binary data as base64
        base64_encoded = base64.b64encode(image_binary).decode('utf-8')
    return base64_encoded

def get_img_positions(html_string):
    index_queue = []
    modified_html = html_string
    search_index = 0
    while True:
        search_index = modified_html.find('<img', search_index+4)
        if search_index == -1:
            break
        src_index = modified_html.find('src', search_index)
        quot_index = modified_html.find('"', src_index)
        index_queue.append(quot_index)
    return index_queue

def replace_img_src(html_string):
    
    positions = get_img_positions(html_string)

    while(positions):
        start_pos = positions.pop()+1
        end_pos = html_string.find('"',start_pos)
        path_to_image = html_string[start_pos:end_pos]
        first_half = html_string[:start_pos]
        second_half = html_string[end_pos:]
        html_string = first_half + image_to_base64(path_to_image) + second_half
        print(path_to_image)

    modified_html = html_string

    return modified_html


# Example usage:
html_string = '<div class="bottom-border topbottomborder"><img src="media/Bottom Border.png" alt="Top" /></div>'
modified_html = replace_img_src(html_string)
#print(modified_html)
