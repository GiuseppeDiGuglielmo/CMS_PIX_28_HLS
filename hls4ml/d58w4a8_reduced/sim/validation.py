import pandas as pd

print('INFO: Load log files')

df0 = pd.read_csv ('accuracy_y_local_0.log', header=None)
df1 = pd.read_csv ('accuracy_y_local_1.log', header=None)
df2 = pd.read_csv ('accuracy_y_local_2.log', header=None)
df3 = pd.read_csv ('accuracy_y_local_3.log', header=None)
df4 = pd.read_csv ('accuracy_y_local_4.log', header=None)
df5 = pd.read_csv ('accuracy_y_local_5.log', header=None)
df6 = pd.read_csv ('accuracy_y_local_6.log', header=None)
df7 = pd.read_csv ('accuracy_y_local_7.log', header=None)
df8 = pd.read_csv ('accuracy_y_local_8.log', header=None)
df9 = pd.read_csv ('accuracy_y_local_9.log', header=None)
df10 = pd.read_csv ('accuracy_y_local_10.log', header=None)
df11 = pd.read_csv ('accuracy_y_local_11.log', header=None)


df = pd.concat([df0, df1, df2, df3, df4, df5, df6, df7, df8, df9, df10, df11], axis=1)

df = df.set_axis(['l0', 'l1', 'l2', 'l3', 'l4', 'l5', 'l6', 'l7', 'l8', 'l9', 'l10', 'l11'], axis=1, inplace=False)


print(df)

print('INFO: Save CSV file')
df.to_csv('hw_accuracy.csv', index=False)

