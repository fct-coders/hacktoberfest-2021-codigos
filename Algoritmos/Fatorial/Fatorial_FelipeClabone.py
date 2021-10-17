def fatorial(x):
    if x < 1:
        return 1
    else:
        return x * fatorial(x-1)

def main():
    numero = int(input("Digite um numero: "))
    resultado = fatorial(numero)
    print(resultado)
    
main()