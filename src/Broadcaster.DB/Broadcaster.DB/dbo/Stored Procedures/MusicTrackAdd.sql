-- =============================================
-- Author:		Pedro Roque, High Precision
-- Create date: 2007-12-04
-- Description:	Adds a new music track, returns the new music ID
-- =============================================
CREATE PROCEDURE [dbo].[MusicTrackAdd]
	@ArtistID int,
	@Title char(100),
	@CategoryID int,
	@LanguageID int,
	@Rythm int,
	@Start int,
	@FadeIn int,
	@Intro int,
	@FadeOut int,
	@Mix int,
	@Finish int,
	@LoopA int=0,
	@LoopB int=0,
	@FileType char(10)='.mp3',
	@MusicTrackID int=0 output
	
AS
BEGIN
	insert into MusicTracks (ArtistID,Title,CategoryID,LanguageID,Rythm,Start,FadeIn,FadeOut,Intro,Mix,Finish,LoopA,LoopB,FileType,Available,Activ)
			values (@ArtistID,@Title,@CategoryID,@LanguageID,@Rythm,@Start,@FadeIn,@FadeOut,@Intro,@Mix,@Finish,@LoopA,@LoopB,@FileType,1,1)

	set @MusicTrackID = scope_identity()
END
