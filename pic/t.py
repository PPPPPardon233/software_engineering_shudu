from PIL import Image

# 打开原始图像
image = Image.open('0.png')

# 获取原始图像的宽度和高度
width, height = image.size

# 计算每个子图像的宽度
sub_width = width // 10

# 分割图像并保存子图像
for i in range(10):
    # 计算子图像的左上角和右下角坐标
    left = i * sub_width
    top = 0
    right = (i + 1) * sub_width
    bottom = height

    # 裁剪子图像
    sub_image = image.crop((left, top, right, bottom))

    # 保存子图像
    sub_image.save(f'0_{i+1}.png')
