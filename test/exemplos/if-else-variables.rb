
numero = 42
pi_aproximado = 3.14159
saudacao = "Olá, mundo!"
primeira_letra = 'C'
ativo = true

resultado_soma = numero + 10
resultado_mult = pi_aproximado * 2.0

eh_maior = numero > 50
condicao_composta = ativo and (numero == 42)

print "Número: ", numero, ", Pi: ", pi_aproximado, ", Saudação: ", saudacao, ", Ativo: ", ativo
puts "Teste concluído!"

if eh_maior
  puts "O número é maior que 50."
elsif condicao_composta
  puts "A condição composta é verdadeira!"
else
  puts "Nenhuma das condições acima foi verdadeira."
end