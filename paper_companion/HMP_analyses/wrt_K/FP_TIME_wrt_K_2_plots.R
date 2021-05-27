
pdf(file="fpr_time_wrt_K.pdf",width=10,height=7)
resetPar <- function() {
  dev.new()
  op <- par(no.readonly = TRUE)
  dev.off()
  op
}
resetPar()

setwd("~/workspace/findere/paper_companion/HMP_analyses/wrt_K")
dev.new()


data = read.table("data_wrtK.txt", head=T)


dev.off()
windows(width = 4.5, height = 4)
opar <- par(no.readonly = TRUE)
# par(cex=1, mai=c(0.1,0.1,0.2,0.1))
par(mar = c(5, 5, 4, 10))
par(fig=c(0,1,0.4,1), mar = par("mar") + c(0, 3, 0, 0))
plot(data$fpr_findere~data$K,xlab="",ylab="FP rate
(%)", lwd=2, pch=15, col="black", 
      type="o",  mgp=c(3,1,0), cex=2, ylim=c(0,5.2),  cex.main = 2, cex.lab = 2, cex.axis = 2)
mtext("findere results depending on K", side=3, line=1, cex=2)
par(new=TRUE)
plot(data$fpr_bf~data$K,xlab="",ylab="", lwd=2, pch=0, col="black", lty=2, axes=FALSE,ylim=c(0,5.2), 
     type="o",  mgp=c(3,1,0), cex=2,  cex.main = 2, cex.lab = 2, cex.axis = 2)
# TIME
par(fig=c(0,1,0,0.6), new = TRUE)
plot(data$time_findere_query~data$K,xlab="K value",ylab="Query time
(s)", lwd=2, pch=15, col="black", 
     type="o",  mgp=c(3,1,0), cex=2, ylim=c(0,23),  cex.main = 2, cex.lab = 2, cex.axis = 2)
par(new=TRUE)
plot(data$time_bf~data$K,xlab="",ylab="", lwd=2, pch=0, col="black", lty=2, axes=FALSE,ylim=c(0,23), 
     type="o",  mgp=c(3,1,0), cex=2,  cex.main = 2, cex.lab = 2, cex.axis = 2)


#par(mar = c(6, 4.1, 4, 5), new = TRUE)
# par(fig=c(0,1,0.0,0.2), new = TRUE)
legend(x = "topright",
       inset = c(-0.3, -0.3), # You will need to fine-tune the second
       # value depending on the windows size
       legend = c("BF", "findere"), 
       lty = c(2, 1),
       # col = c(, 3),
       pch=c(0,15), lwd=1, cex = 1.5,
       xpd = TRUE, # You need to specify this graphical parameter to add
       # the legend outside the plot area
       ) # Horizontal legend. You can also set the number
# of columns with the argument ncol
# if horiz = FALSE

dev.off()


# legend( x="topleft",
#         legend=c("BF", "findere"), cex = 2,
#         col=c("black"), lty=c(2,1),
#         pch=c(0,15), lwd=1,merge=TRUE, bty = "n")

# par(fig=c(0,1,0.0,0.15), new = TRUE)


