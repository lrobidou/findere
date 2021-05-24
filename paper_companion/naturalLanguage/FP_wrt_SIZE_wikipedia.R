
pdf(file="fpr_size_wikipedia.pdf",width=6,height=4)
resetPar <- function() {
  dev.new()
  op <- par(no.readonly = TRUE)
  dev.off()
  op
}
resetPar()


dev.new()



#par(mar=c(5,5,3,6), cex.axis=2, cex.lab=2, cex.main = 2)
# par(mar=c(5,5,3,6))
data = read.table("data_findereOnWikipedia.txt", head=T)
data$sizeGiga = data$size/8000000000
162072792/8000000000

dev.off()
plot(data$FPR_findere~data$sizeGiga,xlab="Bloom Filter size (GB)",ylab="FP rate (%) - log scale",pch=15, 
     col="red", log="y",
     yaxt="n",xaxt="n",
     bg = "red", type="l",  cex=2, main="False positive rate, wikipedia corpus, \
     depending on the Bloom filter size, K=31, z=3", 
     cex.main = 1, cex.lab = 1, cex.axis = 1,
     ylim=c(0.01, 100))
points(data$FPR_BF~data$sizeGiga,type="l",xlab="",ylab="",pch=19, lty=2, col="blue",  cex=1, xlim=c(0, 15))

yticks<-c(0.01,0.03,0.1,1,5,10, 50)
axis(2,at=yticks,labels=yticks)
xticks<-c(0,2,4,6,8,10,12,14,16, 18, 20, 22, 24, 26, 28, 30, 32, 34)
axis(1,at=xticks,labels=xticks)


par(new = TRUE)#, mar=c(5,5,3,6))


segments(-1000, 0.1, 20, 0.1,
         col = par("fg"), lty = 3, lwd = par("lwd"), cex=2)


segments(0.02, 0.000001,  0.02, 0.2,
         col = par("fg"), lty = 3, lwd = par("lwd"), cex=2)

segments(3.83, 0.000001, 3.83, 0.2,
         col = par("fg"), lty = 3, lwd = par("lwd"), cex=2)



par(new = TRUE)#, mar=c(5,5,3,6))

legend( x="top", 
        legend=c("Bloom filter","findere"), 
        col=c("blue","red"), lty=c(2,1),
        lwd=1, merge=TRUE, bty = "n", cex=c(1,1) )


dev.off()



