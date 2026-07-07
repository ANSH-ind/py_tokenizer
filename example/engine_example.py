from py_tokenizer import engine as tokenizer # import engine for large files.
import os

cpu_count = os.cpu_count()

encode_text = tokenizer("story.txt",chunk_s, get_file_info = True, normalize = False , epoch = 20, using_cpu = cou_count, use_thread = True)
#hit the run button or compile the code and then you will see 2 files in your system 1. vocabullary.json in which yiu tokens are included with ids and other once is file_info.json in which your all details of files are included like file path, file size, chunk size, bytes .. 

print("done")

