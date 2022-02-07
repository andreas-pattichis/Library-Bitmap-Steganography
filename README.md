/**

# Bitmap-Steganography-Library

Autors: Andreas Pattichis and Christian Costa

### Operation 1: Prints the header elements of a specified image in the following format.

**Input example:**
$./bmpSteganography –list 4x3.bmp image2.bmp

**Output example:**
BITMAP_FILE_HEADER ==================
bfType: BM
bfSize: 104
bfReserved1: 0
bfReserved2: 0
bfOffBits: 54
BITMAP_INFO_HEADER ==================
biSize: 40
biWidth: 3
biHeight: 4
biPlanes: 1
biBitCount: 24
biCompression: 0 biSizeImage: 50
biXPelsPerMeter: 2677
biYPelsPerMeter: 2677
biClrUsed: 0
biClrImportant: 0

### Operation 2: Grayscale Filter

**Input example:**
$./bmpSteganography –grayscale image1.bmp 

**Output example:**<br />
![image](https://user-images.githubusercontent.com/63289392/152789017-f8956aea-1e4c-43db-a866-891bc8d8ef7d.png)

The –grayscale argument applies the grayscale filter that converts the color of each pixel to shades of gray. 

### Operation 3: Encode a secret image within another image

**Input example:**
$./bmpSteganography –encodeStegano nbBits coverImage.bmp secretImage.bmp

**Output example:**<br />
![image](https://user-images.githubusercontent.com/63289392/152789063-bc2d53f8-7345-42be-8d45-7aca8dcb8be6.png)

The result of performing this operation is to create an image named newcoverImage.bmp which is the cover image with the secret image inside it.

### Operation 4: Decoding/Retrieving a secret image from another image

**Input example:**
$./bmpSteganography –decodeStegano nbBits encryptedImage.bmp

**Output example:**<br />
![image](https://user-images.githubusercontent.com/63289392/152789158-eba664d3-ff9c-41ea-8597-d4a3e9e401a9.png)

The result of performing this operation is to create an image named newencryptedImage.bmp which is the secret image. 

### Operation 5: Encode text within an image

**Input example:**
$./bmpSteganography –encodeText coverImage.bmp inputText.txt

**Output example:**<br />
![image](https://user-images.githubusercontent.com/63289392/152789600-ea1368df-3798-4d4a-9411-c853e88cfde7.png)

The result of performing this operation is to create an image named newcoverImage.bmp which is a bmp image with inputText text embedded in it.txt.

### Operation 6: Decoding/Retrieving secret text from an image

**Input example:**
$./bmpSteganography –decodeText encryptedImage.bmp msgLength output.txt

**Output example:**<br />
![image](https://user-images.githubusercontent.com/63289392/152789645-564ba06d-5d78-4e1b-8d14-19b675add11d.png)

The result of performing this operation is to create a text file with the message retrieved from the encrypted Image encryptedImage.bmp.

### Operation 7: Create a bmp image from text

**Input example:**
$./bmpSteganography –stringToImage sampleImage.bmp inputText.txt

**Output example:**<br />
![image](https://user-images.githubusercontent.com/63289392/152789688-00ee2dc7-4688-4a47-9c1d-e9d73fbb0cdb.png)

In this function the text in the inputText .txt is "converted" to a bmp image which will be a gray image.

### Operation 8: Decoding/Retrieving secret text from a bmp image

**Input example:**
$./bmpSteganography –imageToString encryptedTextImage.bmp

A text file named outputText.txt is created.

*/
