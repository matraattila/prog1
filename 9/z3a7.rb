class Csomopont
  attr_accessor :betu, :bal_nulla, :jobb_egy

  def initialize(betu = '/')
    @betu = betu
    @bal_nulla = nil
    @jobb_egy = nil
  end
end

class LZWBinFa
  def initialize
    @gyoker = Csomopont.new
    @fa = @gyoker
    @melyseg = 0
    @max_melyseg = 0
    @atlag_osszeg = 0
    @atlag_db = 0
    @szoras_osszeg = 0.0
    @atlag = 0.0
  end

  def insert_character(b)
    if b == '0'
      if @fa.bal_nulla.nil?
        @fa.bal_nulla = Csomopont.new('0')
        @fa = @gyoker
      else
        @fa = @fa.bal_nulla
      end
    else
      if @fa.jobb_egy.nil?
        @fa.jobb_egy = Csomopont.new('1')
        @fa = @gyoker
      else
        @fa = @fa.jobb_egy
      end
    end
  end

  def print_tree
    @melyseg = 0
    print_node(@gyoker)
  end

  def get_depth
    @melyseg = 0
    @max_melyseg = 0
    calculate_depth(@gyoker)
    @max_melyseg - 1
  end

  def get_mean
    @melyseg = 0
    @atlag_osszeg = 0
    @atlag_db = 0
    calculate_mean(@gyoker)
    @atlag = @atlag_osszeg.to_f / @atlag_db
    @atlag
  end

  def get_variance
    @atlag = get_mean
    @szoras_osszeg = 0.0
    @melyseg = 0
    @atlag_db = 0
    calculate_variance(@gyoker)
    if @atlag_db - 1 > 0
      Math.sqrt(@szoras_osszeg / (@atlag_db - 1))
    else
      Math.sqrt(@szoras_osszeg)
    end
  end

  private

  def print_node(node)
    return if node.nil?

    @melyseg += 1
    print_node(node.jobb_egy)
    puts "#{'---' * @melyseg}#{node.betu}(#{@melyseg - 1})"
    print_node(node.bal_nulla)
    @melyseg -= 1
  end

  def calculate_depth(node)
    return if node.nil?

    @melyseg += 1
    @max_melyseg = @melyseg if @melyseg > @max_melyseg
    calculate_depth(node.jobb_egy)
    calculate_depth(node.bal_nulla)
    @melyseg -= 1
  end

  def calculate_mean(node)
    return if node.nil?

    @melyseg += 1
    calculate_mean(node.jobb_egy)
    calculate_mean(node.bal_nulla)
    @melyseg -= 1
    if node.jobb_egy.nil? && node.bal_nulla.nil?
      @atlag_db += 1
      @atlag_osszeg += @melyseg
    end
  end

  def calculate_variance(node)
    return if node.nil?

    @melyseg += 1
    calculate_variance(node.jobb_egy)
    calculate_variance(node.bal_nulla)
    @melyseg -= 1
    if node.jobb_egy.nil? && node.bal_nulla.nil?
      @atlag_db += 1
      @szoras_osszeg += (@melyseg - @atlag) ** 2
    end
  end
end

def usage
  puts "Usage: ruby lzwtree.rb in_file -o out_file"
end

if __FILE__ == $0
  if ARGV.length != 3
    usage
    exit(-1)
  end

  in_file = ARGV[0]
  if ARGV[1] != "-o"
    usage
    exit(-2)
  end

  out_file = ARGV[2]

  begin
    data = File.binread(in_file)
  rescue Errno::ENOENT
    puts "#{in_file} does not exist..."
    usage
    exit(-3)
  end

  bin_fa = LZWBinFa.new
  in_comment = false

  data.each_byte do |b|
    if b == '>'.ord
      in_comment = true
      next
    end

    if b == "\n".ord
      in_comment = false
      next
    end

    next if in_comment || b == 'N'.ord

    8.times do
      if b & 0x80 != 0
        bin_fa.insert_character('1')
      else
        bin_fa.insert_character('0')
      end
      b <<= 1
    end
  end

  File.open(out_file, "w") do |file|
    bin_fa.print_tree
    file.puts "depth = #{bin_fa.get_depth}"
    file.puts "mean = #{'%.2f' % bin_fa.get_mean}"
    file.puts "var = #{'%.2f' % bin_fa.get_variance}"
  end
end
