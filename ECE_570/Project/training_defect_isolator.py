import xml.etree.ElementTree as ET
from PIL import Image
import os

# Assuming the script is in the same directory as the image and XML file folders
script_directory = os.path.dirname(os.path.realpath(__file__))

# Folder names
image_folder_name = "pcb_defective"
xml_folder_name = "annotations"
output_folder_name = "training_defects"

# Full paths
image_folder_path = os.path.join(script_directory, image_folder_name)
xml_folder_path = os.path.join(script_directory, xml_folder_name)
output_folder_path = os.path.join(script_directory, output_folder_name)

# Create the 'training_defects' folder if it doesn't exist
if not os.path.exists(output_folder_path):
    os.makedirs(output_folder_path)

# Iterate over each XML file in the 'annotations' folder
for xml_file_name in os.listdir(xml_folder_path):
    if xml_file_name.endswith(".xml"):
        # Construct the full path to the XML file
        xml_file_path = os.path.join(xml_folder_path, xml_file_name)

        # Parse the XML file
        tree = ET.parse(xml_file_path)
        root = tree.getroot()

        # Get the corresponding image file path
        image_file_name = root.find('filename').text
        image_path = os.path.join(image_folder_path, image_file_name)

        # Get the folder name (e.g., 'Missing_hole')
        folder_name = root.find('folder').text
        category = 0

        if folder_name == 'Missing_hole':
            category = 0
        elif folder_name == 'Mouse_bite':
            category = 1
        elif folder_name == 'Open_circuit':
            category = 2
        elif folder_name == 'Short':
            category = 3
        elif folder_name == 'Spur':
            category = 4
        elif folder_name == 'Spurious_copper':
            category = 5

        # Loop through each object in the annotation
        for obj in root.findall('.//object'):
            # Get coordinates
            xmin = int(obj.find('bndbox/xmin').text)
            ymin = int(obj.find('bndbox/ymin').text)
            xmax = int(obj.find('bndbox/xmax').text)
            ymax = int(obj.find('bndbox/ymax').text)

            # Open the image using PIL
            image = Image.open(image_path)

            # Crop the region
            cropped_image = image.crop((xmin, ymin, xmax, ymax))

            # Resize the cropped image to 64x64
            resized_image = cropped_image.resize((64, 64))

            # Save the resized image in the 'training_defects' folder
            output_file_path = os.path.join(output_folder_path, f"{category}_{folder_name}_resizednum_{xmin}.jpg")
            resized_image.save(output_file_path)

# Inform the user that the process is complete
print("Images saved successfully in 'training_defects' folder.")