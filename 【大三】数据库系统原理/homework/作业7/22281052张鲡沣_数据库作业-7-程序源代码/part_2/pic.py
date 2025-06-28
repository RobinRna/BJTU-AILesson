import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns  # 可选，用于更好看的图表样式

plt.rcParams['font.sans-serif'] = ['SimHei']  # 指定默认字体为黑体
plt.rcParams['axes.unicode_minus'] = False   # 解决保存图像是负号'-'显示为方块的问题

# --- 读取CSV数据 ---

df = pd.read_csv('query_performance.csv')

# --- 数据预处理 ---
if df.empty:
    exit()

try:
    df['DataScale'] = pd.to_numeric(df['DataScale'])
    df['QueryTimeMillis'] = pd.to_numeric(df['QueryTimeMillis'])
    # 将IndexExists转换为更易读的标签，如果它还不是
    if df['IndexExists'].dtype == 'bool':
        df['IndexStatus'] = df['IndexExists'].apply(
            lambda x: '有索引' if x else '无索引')
    elif df['IndexExists'].dtype == 'object':  # 如果已经是字符串 "True"/"False"
        df['IndexStatus'] = df['IndexExists'].apply(
            lambda x: '有索引' if x.lower() == 'true' else '无索引')
    else:  # 其他情况，尝试直接转换
        df['IndexStatus'] = df['IndexExists'].astype(str)

    print("数据预处理完成。")
except:
    exit()

# 分离有索引和无索引的数据
df_no_index = df[df['IndexStatus'] == '无索引']
df_with_index = df[df['IndexStatus'] == '有索引']

if df_no_index.empty or df_with_index.empty:
    print("警告: '无索引' 或 '有索引' 的数据为空，部分图表可能无法正确生成。")


sns.set_theme(style="whitegrid", font='SimHei')

# --- 1. 折线图对比：不同数据规模下有无索引的查询时间 ---
plt.figure(figsize=(12, 7))  # 调整图像大小
if not df_no_index.empty:
    plt.plot(df_no_index['DataScale'], df_no_index['QueryTimeMillis'],
             marker='o', linestyle='-', label='无索引')
if not df_with_index.empty:
    plt.plot(df_with_index['DataScale'], df_with_index['QueryTimeMillis'],
             marker='x', linestyle='--', label='有索引')

plt.title('不同数据规模下有无索引的查询时间对比', fontsize=16)
plt.xlabel('数据规模 (记录数)', fontsize=14)
plt.ylabel('平均查询时间 (毫秒)', fontsize=14)
if not df.empty:
    plt.xticks(df['DataScale'].unique(), rotation=45,
               ha="right")  # 确保X轴刻度为实际的数据规模，并旋转避免重叠
else:
    plt.xticks([])
plt.tick_params(axis='both', which='major', labelsize=12)  # 调整刻度标签大小
plt.legend(fontsize=12)
plt.grid(True)
plt.tight_layout()  # 自动调整布局，防止标签重叠
try:
    plt.savefig('query_performance_line_chart.png')
    print("折线图已保存为 query_performance_line_chart.png")
except Exception as e:
    print(f"保存折线图失败: {e}")
plt.show()


plt.figure(figsize=(14, 8))  # 调整图像大小
if not df.empty:
    sns.barplot(x='DataScale', y='QueryTimeMillis', hue='IndexStatus',
                data=df, palette={'无索引': 'skyblue', '有索引': 'lightcoral'})
    plt.title('不同数据规模下有无索引的查询时间对比', fontsize=16)
    plt.xlabel('数据规模 (记录数)', fontsize=14)
    plt.ylabel('平均查询时间 (毫秒)', fontsize=14)
    plt.xticks(rotation=45, ha="right")  # 旋转X轴刻度标签
    plt.tick_params(axis='both', which='major', labelsize=12)
    plt.legend(title='索引状态', fontsize=12, title_fontsize=13)
    plt.grid(True, axis='y')
    plt.tight_layout()
    try:
        plt.savefig('query_performance_bar_chart.png')
        print("分组柱状图已保存为 query_performance_bar_chart.png")
    except Exception as e:
        print(f"保存分组柱状图失败: {e}")
    plt.show()
else:
    print("数据为空，跳过分组柱状图绘制。")


# 计算性能提升百分比: (无索引时间 - 有索引时间) / 无索引时间 * 100%
if not df_no_index.empty and not df_with_index.empty:
    df_merged = pd.merge(df_no_index[['DataScale', 'QueryTimeMillis']],
                         df_with_index[['DataScale', 'QueryTimeMillis']],
                         on='DataScale',
                         suffixes=('_无索引', '_有索引'))
    # 避免除以零的错误，如果无索引时间为0，则提升设为0或NaN
    df_merged['PerformanceImprovement'] = df_merged.apply(
        lambda row: ((row['QueryTimeMillis_无索引'] -
                     row['QueryTimeMillis_有索引']) / row['QueryTimeMillis_无索引']) * 100
        if row['QueryTimeMillis_无索引'] > 0 else 0, axis=1
    )

    if not df_merged.empty:
        plt.figure(figsize=(12, 7))  # 调整图像大小
        sns.barplot(x='DataScale', y='PerformanceImprovement',
                    data=df_merged, color='mediumseagreen')

        plt.title('不同数据规模下使用索引带来的查询性能提升百分比', fontsize=16)
        plt.xlabel('数据规模 (记录数)', fontsize=14)
        plt.ylabel('性能提升百分比 (%)', fontsize=14)
        plt.xticks(rotation=45, ha="right")
        plt.tick_params(axis='both', which='major', labelsize=12)
        plt.grid(True, axis='y')
        plt.axhline(0, color='grey', linewidth=0.8)  # 添加一条y=0的参考线
        plt.tight_layout()
        try:
            plt.savefig('performance_improvement_chart.png')
            print("性能提升百分比图已保存为 performance_improvement_chart.png")
        except Exception as e:
            print(f"保存性能提升百分比图失败: {e}")
        plt.show()
    else:
        print("合并后的数据为空，无法计算性能提升，跳过性能提升百分比图绘制。")
else:
    print("'无索引'或'有索引'的数据不完整，无法计算性能提升")
