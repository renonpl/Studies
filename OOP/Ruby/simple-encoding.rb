class Open
	def initialize(word)
		@word = word
	end
	def value
		@word
	end
	def encrypt(key)
		temp = @word
		i = 0
		while i < temp.size do
		temp[i] = key[temp[i]]
		i += 1
		end
		return Encrypted.new(temp)
	end
end

class Encrypted
	def initialize(word)
		@word = word
	end
	def value
		@word
	end
	def decode(key)
		temp = @word
		i = 0	
		while i < temp.size do
		temp[i] = key.index(temp[i])
		i += 1
		end
		return Open.new(temp)
	end
end


temp = Open.new("ruby")
slownik = {'a' => 'b', 'b' => 'r','r' => 'y', 'y' => 'u', 'u' => 'a'}
szyfer = temp.encrypt(slownik)
puts szyfer.value
rozkod = szyfer.decode(slownik)
puts rozkod.value


temp2 = Open.new("abiru")
slownik2 = {'a' => 'z', 'b' => 'r','r' => 'y', 'y' => 'u', 'u' => 'a', 'i' => 'o'}
szyfer2 = temp2.encrypt(slownik2)
puts szyfer2.value
rozkod2 = szyfer2.decode(slownik2)
puts rozkod2.value