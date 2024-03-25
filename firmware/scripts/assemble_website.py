print("Assembling Website")

def insert_html_into_header(html_file, header_file):
    # Read the contents of the HTML file
    with open(html_file, 'r') as html_file:
        html_content = html_file.read()

    html_content = html_content.replace('"', '\\"')
    # Replace newlines with escaped newlines and add quotation marks to each line
    html_content = html_content.replace('\n', '\\n"\n"')
    # Construct the content to be inserted into the header file
    header_content = """#ifndef WEBCONTROLLER_H
#define WEBCONTROLLER_H

const char *web_html = \"{}\"
                      \"\";

#endif""".format(html_content)

    # Write the combined content into the header file
    with open(header_file, 'w') as header_file:
        header_file.write(header_content)

# Replace 'web_controller.html' and 'web_controller.h' with your file paths
insert_html_into_header("firmware\include\web_controller.html", 'firmware\include\web_controller.h')
