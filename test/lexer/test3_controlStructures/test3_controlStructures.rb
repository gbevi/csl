age = 24

if age == 24
    puts "age: 24"
elsif age != 24
    if age <= 24
        puts "age: menor ou igual a 24"
    elsif age >= 24
        puts "age: maior ou igual a 24"
    elsif age < 24
        puts "age: menor que 24"
    elsif age > 24
        puts "age: maior que 24"
    else
        puts "erro"
    end
    
i = 0

while i < 5
    puts i
    i = i + 1
end

for i in 1..5
    puts "Número #{i}"
end

3.times do |i|
    puts "Bloco do #{i}"
    end