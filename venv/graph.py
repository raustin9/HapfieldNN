import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import re

data = open('data.txt', 'r')
d = data.readlines()
df = pd.DataFrame()

print(d)

df['imprints'] = [i for i in range(1, 51)]

j = 1
for i in range(0, len(d), 3):
    temp1 = re.sub(r'[\[\]]', '', d[i])
    df[f'stable_{j}'] = [s.strip() for s in temp1.split(',')]

    temp2 = re.sub(r'[\[\]]', '', d[i+1])
    df[f'frac_stable_{j}'] = [s.strip() for s in temp2.split(',')]

    temp3 = re.sub(r'[\[\]]', '', d[i+2])
    df[f'frac_unstable_{j}'] = [s.strip() for s in temp3.split(',')]
    j += 1

df = df.apply(pd.to_numeric)
# display(df)

ax1 = sns.lineplot(df['frac_unstable_1'], label="Experiment 1")
ax2 = sns.lineplot(df['frac_unstable_2'], label="Experiment 2")
ax3 = sns.lineplot(df['frac_unstable_3'], label="Experiment 3")
ax4 = sns.lineplot(df['frac_unstable_4'], label="Experiment 4")
ax5 = sns.lineplot(df['frac_unstable_5'], label="Experiment 5")

ax1.set(xlabel='Number of Imprints', ylabel='Fraction of Unstable Imprints')
plt.savefig('figures/unstable.png')
plt.show()

plt.clf()

list1 = list(zip(list(df['imprints']), list(df['frac_unstable_1'])))
list2 = list(zip(list(df['imprints']), list(df['frac_unstable_2'])))
list3 = list(zip(list(df['imprints']), list(df['frac_unstable_3'])))
list4 = list(zip(list(df['imprints']), list(df['frac_unstable_4'])))
list5 = list(zip(list(df['imprints']), list(df['frac_unstable_5'])))

data = list1 + list2 + list3 + list4 + list5
# print(data)

zipped_data = pd.DataFrame(data, columns=['imprints', 'score'])
# display(zipped_data)


ax = sns.lineplot(zipped_data, x='imprints', y='score')
ax.set(xlabel='Number of Imprints', ylabel='Fraction of Unstable Imprints')
plt.savefig('figures/unstable_avg.png')
plt.show()

plt.clf()

ax1 = sns.lineplot(df['stable_1'], label="Experiment 1")
ax2 = sns.lineplot(df['stable_2'], label="Experiment 2")
ax3 = sns.lineplot(df['stable_3'], label="Experiment 3")
ax4 = sns.lineplot(df['stable_4'], label="Experiment 4")
ax5 = sns.lineplot(df['stable_5'], label="Experiment 5")

ax1.set(xlabel='Number of Imprints', ylabel='Stable Imprints')
plt.savefig('figures/stable.png')
plt.show()

plt.clf()

list1 = list(zip(list(df['imprints']), list(df['stable_1'])))
list2 = list(zip(list(df['imprints']), list(df['stable_2'])))
list3 = list(zip(list(df['imprints']), list(df['stable_3'])))
list4 = list(zip(list(df['imprints']), list(df['stable_4'])))
list5 = list(zip(list(df['imprints']), list(df['stable_5'])))

data = list1 + list2 + list3 + list4 + list5
# print(data)

zipped_data = pd.DataFrame(data, columns=['imprints', 'score'])
# display(zipped_data)


ax = sns.lineplot(zipped_data, x='imprints', y='score')
ax.set(xlabel='Number of Imprints', ylabel='Stable Imprints')
plt.savefig('figures/stable_avg.png')
plt.show()
