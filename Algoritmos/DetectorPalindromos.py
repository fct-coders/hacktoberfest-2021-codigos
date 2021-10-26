def checa_palindromo(string):
    reversed_string = string[::-1]
    status = 1
    if( string != reversed_string ):
        status = 0
    return status

string = input("Digite o texto: ")
status = checa_palindromo(string)
if( status ):
    print("Palindromo encontrado")
else:
    print("Não é palindromo")