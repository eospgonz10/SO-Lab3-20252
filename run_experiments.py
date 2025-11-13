import argparse
import csv
import subprocess
import sys
import shlex
from statistics import mean
import os
import math

def parse_time_from_output(output: str):
    # Busca la línea que contiene 'CalcPi time (seconds):'
    for line in output.splitlines():
        if 'CalcPi time (seconds):' in line:
            try:
                return float(line.split(':')[-1].strip())
            except Exception:
                return None
    return None

def run_command(cmd):
    try:
        proc = subprocess.run(shlex.split(cmd), capture_output=True, text=True, timeout=36000)
        return proc.returncode, proc.stdout + proc.stderr
    except subprocess.TimeoutExpired:
        return 1, 'TIMEOUT'

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--n', type=int, required=True, help='Número de intervalos (n)')
    parser.add_argument('--threads', type=int, nargs='+', default=None, help='Lista de hilos para pi_p (si se omite usa 1,2,4,... hasta 2x núcleos)')
    parser.add_argument('--repeats', type=int, default=3, help='Repeticiones por caso')
    parser.add_argument('--out', type=str, default='results.csv', help='Archivo CSV de salida')
    args = parser.parse_args()

    n = args.n
    threads_list = args.threads
    if threads_list is None:
        # Generar lista estándar: 1,2,4,8,... hasta 2 * cpu_count
        cpu = os.cpu_count() or 1
        max_threads = max(1, 2 * cpu)
        threads_list = []
        t = 1
        while t <= max_threads:
            threads_list.append(t)
            t *= 2
                    
        threads_list = sorted(set(threads_list))
    repeats = args.repeats
    out_file = args.out

    rows = []

    # Ejecutar pi_s repeats veces
    for r in range(repeats):
        cmd = f'./pi_s {n}'
        rc, out = run_command(cmd)
        t = parse_time_from_output(out)
        rows.append({'program':'pi_s','threads':1,'n':n,'repeat':r+1,'time':t,'rc':rc})

    # Ejecutar pi_p para cada número de hilos
    for T in threads_list:
        for r in range(repeats):
            cmd = f'./pi_p {n} {T}'
            rc, out = run_command(cmd)
            t = parse_time_from_output(out)
            rows.append({'program':'pi_p','threads':T,'n':n,'repeat':r+1,'time':t,'rc':rc})

    # Guardar CSV
    fieldnames = ['program','threads','n','repeat','time','rc']
    with open(out_file, 'w', newline='') as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        for row in rows:
            writer.writerow(row)

    print(f'Results written to {out_file}')

if __name__ == '__main__':
    main()
