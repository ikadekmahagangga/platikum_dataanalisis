import sqlite3
import pandas as pd
import matplotlib.pyplot as plt

# membuat koneksi dengan database Titanic
conn = sqlite3.connect('titanic.db')

# query untuk menampilkan jumlah penumpang yang selamat dan tidak selamat
survived_query = "SELECT COUNT(*) FROM passenger WHERE survived = 1"
not_survived_query = "SELECT COUNT(*) FROM passenger WHERE survived = 0"

survived = pd.read_sql_query(survived_query, conn)
not_survived = pd.read_sql_query(not_survived_query, conn)

print("Jumlah penumpang Titanic yang selamat:", survived.iloc[0]['COUNT(*)'])
print("Jumlah penumpang Titanic yang tidak selamat:", not_survived.iloc[0]['COUNT(*)'])

# query untuk menampilkan jumlah penumpang pria dan wanita
male_query = "SELECT COUNT(*) FROM passenger WHERE sex = 'male'"
female_query = "SELECT COUNT(*) FROM passenger WHERE sex = 'female'"

male = pd.read_sql_query(male_query, conn)
female = pd.read_sql_query(female_query, conn)

print("Jumlah penumpang pria di Titanic:", male.iloc[0]['COUNT(*)'])
print("Jumlah penumpang wanita di Titanic:", female.iloc[0]['COUNT(*)'])

# query untuk menampilkan distribusi usia penumpang Titanic
age_query = "SELECT age FROM passenger WHERE age NOT NULL"

age = pd.read_sql_query(age_query, conn)

plt.hist(age['age'], bins=20)
plt.title('Distribusi Usia Penumpang Titanic')
plt.xlabel('Usia')
plt.ylabel('Frekuensi')
plt.show()

# menutup koneksi dengan database
conn.close()
