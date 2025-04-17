import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# 读取数据文件 (假设列间以空格分隔)
df = pd.read_csv('./attack800for13', sep='\s+', header=None)

# 提取关键列 (第3列为x轴，倒数第2列为y轴)
x = df[2].values  # 第三列 (0-255)
y = df.iloc[:, -2].values  # 倒数第二列

# 创建画布
plt.figure(figsize=(12, 6), dpi=100)

# 绘制散点图
plt.scatter(x, y, s=8, alpha=0.6, label='Data Points')

# 标注最大值点
max_idx = np.argmax(y)
plt.scatter(x[max_idx], y[max_idx], color='red', s=80, 
            label=f'Max Value (x={x[max_idx]}, y={y[max_idx]:.3f})')
plt.annotate(f'x={x[max_idx]}\ny={y[max_idx]:.3f}', 
             (x[max_idx], y[max_idx]),
             textcoords="offset points",
             xytext=(10,-15),
             ha='left',
             arrowprops=dict(arrowstyle="->", color='red'))

# 添加标签和标题
plt.xlabel('X (Third Column)')
plt.ylabel('Y (Second Last Column)')
plt.title('Study400for13 Data Analysis')
plt.grid(alpha=0.3)
plt.legend()

# 设置x轴范围 (0-255)
plt.xlim(-5, 260)

# 保存图片
plt.savefig('study800for13.jpg', bbox_inches='tight', quality=90)
plt.close()