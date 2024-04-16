print("Assembling Website")

from collections import deque
import base64
import os

original_dir = os.getcwd()

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

def read_file(file_path):
    with open(file_path, 'r') as file:
        content = file.read()
        return content

def get_html_from_file(html_file_path):
    with open(html_file_path, 'r') as html_file:
        html_content = html_file.read()
    return html_content

def insert_css_into_html(key, html_string ,file_path):
    with open(file_path, 'r') as file:
        css_content = file.read()
        return html_string.replace(key, css_content)

def replace_img_in_html(html_string):
    
    positions = get_img_positions(html_string)

    while(positions):
        start_pos = positions.pop()+1
        end_pos = html_string.find('"',start_pos)
        path_to_image = html_string[start_pos:end_pos]
        first_half = html_string[:start_pos]
        second_half = html_string[end_pos:]
        html_string = first_half + "data:image/png;base64," + image_to_base64(path_to_image) + second_half
        print(path_to_image)

    modified_html = html_string

    return modified_html

def remove_html_comments(html_string):
    # Regular expression to match HTML comments
    comment_pattern = r'<!--(.*?)-->'
    
    # Remove HTML comments using re.sub
    return re.sub(comment_pattern, '', html_string)

def insert_javascript_into_html(key, html_content ,js_path):
    with open(js_path, 'r') as file:
        js_content = file.read()
        html_content = html_content.replace(key, '<script>'+js_content+'</script>')
        return html_content
    
def convert_html_string_to_header(html_content, title):

    html_content = html_content.replace('"', '\\"')
    # Replace newlines with escaped newlines and add quotation marks to each line
    html_content = html_content.replace('\n', '\\n"\n"')
    # Construct the content to be inserted into the header file
    header_content = """#pragma once

const char *"""+title+""" = \"{}\"
                      \"\";
""".format(html_content)
    return header_content

def write_to_file(contents, path):
    with open(path, 'w') as file:
        file.write(contents)

def write_html_formatted_string_to_header(html_content, file_path):
    global original_dir
    os.chdir(original_dir)
    with open(file_path, 'w') as file:
        file.write(html_content)

def convert_html_file(html_file_path, output_file_path):
    html_page = get_html_from_file(html_file_path)
    html_page = insert_css_into_html("this_gets_replaced{width: 80px;}",html_page,"firmware\webpage\styles.css")
    original_dir = os.getcwd()
    dird = os.path.split(os.path.abspath(html_file_path))[0]
    print(dird)
    os.chdir(dird)
    html_page  = replace_img_in_html(html_page)
    os.chdir(original_dir)
    html_page = convert_html_string_to_header(html_page, "web_html")
    write_html_formatted_string_to_header(html_page, output_file_path)

def write_js_to_header(input_file_path, output_file_path):
    with open(input_file_path, 'r') as file:
        js_content = file.read()
        js_content = js_content.replace('"', '\\"')
        js_content = js_content.replace('\n', '\\n"\n"')
        header_content = """#pragma once

const char *scripts = \"{}\"
                      \"\";

""".format(js_content)
        with open(output_file_path, 'w') as file:
            file.write(header_content)

def format_c_header(content, name):
    content = content.replace('"', '\\"')
    content = content.replace('\n', '\\n"\n"')
    header_content = """#pragma once

const char *"""+name+""" = \"{}\"
                      \"\";

""".format(content)
    return header_content
    
def extract_filename(file_path):
    # Split the file path into directory and filename
    directory, filename_with_extension = os.path.split(file_path)
    
    # Split the filename to remove the extension
    filename, extension = os.path.splitext(filename_with_extension)
    
    return filename

def convert_js(js_file_path):
    js_contents = read_file(js_file_path)
    var_name = extract_filename(js_file_path)
    js_contents = format_c_header(js_contents, var_name)
    write_to_file(js_contents, "firmware/include/"+var_name+".h")

def convert_html(html_file_path):
    html_contents = read_file(html_file_path)
    
    original_dir = os.getcwd()
    image_dir = os.path.split(os.path.abspath(html_file_path))[0]
    os.chdir(image_dir)
    html_contents  = replace_img_in_html(html_contents)
    os.chdir(original_dir)

    var_name = extract_filename(html_file_path)
    html_contents = format_c_header(html_contents, var_name)
    write_to_file(html_contents, "firmware/include/"+var_name+".h")
    
def convert_css(css_file_path):
    pass

convert_js("firmware/webpage/scripts.js")
convert_html("firmware/webpage/web_controller.html")
convert_html('firmware/webpage/battery.html')
convert_js("firmware/webpage/styles.css")



