from pathlib import Path

'''
  Скрипт подсчитывает общее количество строк в .h и .cpp файлах
'''

def count_lines(directory):
    total_lines = 0

    for extension in ("*.h", "*.cpp"):
        for file in Path(directory).rglob(extension):
            try:
                with open(file, "r", encoding="utf-8", errors="ignore") as f:
                    lines = sum(1 for _ in f)
                    total_lines += lines
                    print(f"{file}: {lines} строк")
            except Exception as e:
                print(f"Не удалось обработать {file}: {e}")
    return total_lines

if __name__ == "__main__":
    print("\nВсего строк:", count_lines("../import") + count_lines("../src"))