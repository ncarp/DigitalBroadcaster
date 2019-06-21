CREATE VIEW [dbo].[ViewMusicData_Playing]
AS
SELECT     dbo.Artists.Name AS Artist, dbo.MusicTracks.Title, dbo.HD.Path, dbo.MusicTracks.ID, dbo.MusicTracks.ArtistID, dbo.MusicTracks.Rythm, 
                      dbo.MusicTracks.Start, dbo.MusicTracks.FadeIn, dbo.MusicTracks.Intro, dbo.MusicTracks.FadeOut, dbo.MusicTracks.Mix, dbo.MusicTracks.Finish, 
                      dbo.MusicTracks.LoopA, dbo.MusicTracks.LoopB, dbo.MusicTracks.FileType
FROM         dbo.MusicTracks INNER JOIN
                      dbo.Artists ON dbo.MusicTracks.ArtistID = dbo.Artists.ID INNER JOIN
                      dbo.HD ON dbo.MusicTracks.PathID = dbo.HD.ID


