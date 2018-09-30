class Fixnum
public
	def factorization
		i = 1
		tab = []
		while i <= self do
			if(self % i == 0)
			 tab.push(i)
			end
			i += 1
		end
		return tab
	end
	def ack(y)
		if self == 0
			 return y + 1
		else
			if y == 0
				return (self-1).ack(1)
			else
				return (self-1).ack(self.ack(y-1))
			end
		end
	end
	def perfect
		tab = self.factorization
		i = 0
		counter = 0
		while i < tab.size do
			counter += tab[i]
			i += 1
		end
		if counter == 2 * self
			 true
		else
		 false
		end
	end
	def toString
		i = self%10
		temp = ""
		case i
		when 0 
			temp = "zero"
		when 1 
			temp = "one"
		when 2
			temp = "two"
		when 3 
			temp = "three"
		when 4 
			temp = "four"
		when 5 
			temp = "five"
		when 6 
			temp = "six"
		when 7 	
			temp = "seven"
		when 8 
			temp = "eight"
		when 9 
			temp = "nine"
		end
		if self/10 == 0
			return temp
		else
			return (self/10).toString + temp
		end
	end
end

tab = 6.factorization
puts tab
x = 2.ack(1)
puts x
puts 6.perfect
puts 28.perfect
puts 5.perfect
puts 0.toString
puts 5142.toString