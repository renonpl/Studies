	class Function
	def initialize(proc)
		@proc = proc
	end
	def value(x)
		return @proc.call(x)
	end
	def roots(a,b,e)
		tab = []
		i = a
		while i < b do
			f = self.value(i)
			if(f < e && -1*e < f)
				tab.push(i)
			end
			i += e
		end
		if 0 == tab.size
			return nil
		end
		return tab
	end
	def area(a,b)
		eps = 0.001
		i = a
		pole = 0
		while i < b do
			pole += eps * self.value(i)
			i += eps
		end
		return pole
	end
	def derivative(x)
		eps = 0.0001
		return (self.value(x+eps) - self.value(x))/eps
	end
end

class Function2
	def initialize(proc)
		@proc = proc
	end
	def value(x,y)
		return @proc.call(x,y)
	end
	def volume(a,b,c,d)
		eps = 0.01
		v = 0
		i = a
		while i < c do
			j = b
			while j < d do
				v += eps * eps * self.value(i,j)
				j += eps
			end
			i += eps
		end
		return v
	end
	def contour(a,b,c,d,height)
		tab = []
		eps = 0.1
		eps_h = 0.1
		i = a
		while i < c do
			j = b
			while j < d do
				f = self.value(i,j)
				if(f < height + eps_h && f > height - eps_h)
					tab.push([i,j])
				end
				j += eps
			end
			i += eps
		end
		return tab
	end
end


funka = Function.new(Proc.new {|n| n*n*2-5})

puts "value  in 5"
puts funka.value(5)
puts "derivative"
puts funka.derivative(3)
puts funka.area(0,5)
puts "roots"
puts funka.roots(-3,7,0.01)

puts "with two arguments"
fun = Function2.new(Proc.new {|a,b| a*5+3*b})
puts fun.value(1,1)
puts "volume"
puts fun.volume(0,0,5,7)
puts "contour"
puts fun.contour(0,0,1,1,5)